/*
 * This is a port of pico_lightshow program to esp32 chip
 */
#include <Arduino.h>
#include <random>
#include <stdio.h>
#include "LightShow.h"

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

PIXEL_COLOR* randomColor(void) {
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

PIXEL_COLOR CHRISTMAS_COLOURS[] ={RED, GREEN, BLUE, YELLOW, PUMPKIN};

PIXEL_COLOR* christmasColor() {
    return  &CHRISTMAS_COLOURS[christmas_distr(gen)];
}

PIXEL_COLOR* christmas() {
    int i = (level++) % 5;
    return  &CHRISTMAS_COLOURS[i];
}

LightShow lightShow(NUM_PIXELS, PIN_NEO_PIXEL, NEO_RGB + NEO_KHZ800);

static uint8_t adjust (uint8_t value) {
    return ((value * time_distr(gen))) ;
}
static uint8_t brightness (uint8_t value) {
    return ((value / time_distr(gen))) ;
}

void setup() {
    lightShow.begin();
}

void loop() {
    printf("Starting loop\n");
    lightShow.rgb(christmas, brightness);
    delay(60*1000);
    lightShow.glowing(christmasColor(), CYCLEDELAY, adjust);
    delay(2000);
    lightShow.sparkle(christmasColor(), 30, DELAY_INTERVAL);
    delay(2000);
    lightShow.colorWipe(randomColor);
    delay(2000);
    lightShow.theaterChase(christmasColor(), DELAY_INTERVAL);
    delay(2000);
    lightShow.rainbow();
    delay(2000);
    lightShow.rainbowChase();
    delay(2000);
    lightShow.theaterChaseRainbow(DELAY_INTERVAL);
    delay(2000);
    printf("Ending loop\n");
}
