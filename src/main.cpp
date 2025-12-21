/*
 * This is a port of pico_lightshow program to esp32 chip
 */
#include <random>
#include <stdio.h>
#include "LightShow.h"
#include "thingProperties.h"

#define PIN_NEO_PIXEL  0     // The ESP32C3 pin that connects to NeoPixel
#define NUM_PIXELS     150  // The number of LEDs (pixels) on NeoPixel
#define DELAY_INTERVAL 100

PIXEL_COLOR pixelColor;
static uint8_t level = 0;

std::uniform_int_distribution<> distr(0, 255);
std::uniform_int_distribution<> time_distr(1, 10);
std::uniform_int_distribution<> christmas_distr(0, 4);
std::random_device dev;
std::mt19937 gen(dev());

PIXEL_COLOR *randomColor(void) {
    pixelColor.r = distr(gen);
    pixelColor.g = distr(gen);
    pixelColor.b = distr(gen);
    return &pixelColor;
}

PIXEL_COLOR RED = PIXEL_COLOR(255, 0, 0);
PIXEL_COLOR GREEN = PIXEL_COLOR(0, 255, 0);
PIXEL_COLOR BLUE = PIXEL_COLOR(0, 0, 255);
PIXEL_COLOR YELLOW = PIXEL_COLOR(255, 222, 33);
PIXEL_COLOR PUMPKIN(255, 45, 0);

PIXEL_COLOR CHRISTMAS_COLOURS[] = {RED, GREEN, BLUE, YELLOW, PUMPKIN};

PIXEL_COLOR *christmasColor() {
    return &CHRISTMAS_COLOURS[christmas_distr(gen)];
}

PIXEL_COLOR *christmas() {
    int i = (level++) % 5;
    return &CHRISTMAS_COLOURS[i];
}

LightShow lightShow(NUM_PIXELS, PIN_NEO_PIXEL, NEO_RGB + NEO_KHZ800);

static uint8_t adjust(uint8_t value) {
    return ((value * time_distr(gen)));
}

static uint8_t brightness(uint8_t value) {
    return ((value / time_distr(gen)));
}

void taskLightshow(void *pvParameters);

void taskArduinoCloud(void *pvParameters);

TaskHandle_t taskHandleLightshow;

void setup() {
    // Initialize serial and wait for port to open:
    Serial.begin(9600);
    // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
    delay(1500);
    lightShow.begin();
    xTaskCreate(
        taskLightshow
        , "TaskLightshow"
        , 4096
        , NULL
        , 1
        , &taskHandleLightshow);
    // Defined in thingProperties.h
    initProperties();

    // Connect to Arduino IoT Cloud
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);

    /*
       The following function allows you to obtain more information
       related to the state of network and IoT Cloud connection and errors
       the higher number the more granular information you’ll get.
       The default is 0 (only errors).
       Maximum is 4
   */
    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();
    pwrSwitch = true;
}

void loop() {
    ArduinoCloud.update();
}


void taskLightshow(void *pvParameters) {
    (void) pvParameters;

    while (1) {
        printf("Starting loop\n");
        lightShow.solid(christmas, brightness);
        vTaskDelay(60 * 1000);
        lightShow.glowing(christmasColor(), CYCLEDELAY, adjust);
        vTaskDelay(2000);
        lightShow.sparkle(christmasColor(), 30, DELAY_INTERVAL);
        vTaskDelay(2000);
        lightShow.colorWipe(randomColor);
        vTaskDelay(2000);
        lightShow.theaterChase(christmasColor(), DELAY_INTERVAL);
        vTaskDelay(2000);
        lightShow.rainbow();
        vTaskDelay(2000);
        lightShow.rainbowChase();
        vTaskDelay(2000);
        lightShow.theaterChaseRainbow(DELAY_INTERVAL);
        vTaskDelay(2000);
        printf("Ending loop\n");
    }
}


/*
  Since PwrSwitch is READ_WRITE variable, onPwrSwitchChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPwrSwitchChange() {
    printf("Updated Switch to %d\n", pwrSwitch);
    printf("task handle Lightshow: %p\n", taskHandleLightshow);
    if (pwrSwitch == true) {
        if (taskHandleLightshow == NULL) {
            printf("POWER ON\n");
            esp_restart();
        }
    } else {
        printf("POWER OFF\n");
        vTaskDelete(taskHandleLightshow);
        taskHandleLightshow = NULL;
        printf("taskLightshow deleted: %p\n", taskHandleLightshow);
        // Turn off lights
        lightShow.clear();
    }
}
