//
// Created by Yuri Moiseyenko on 2024-10-14.
//
#include "LightShow.h"
#include "br_iterator.h"
#include "range.h"
#include <random>

std::random_device device;
std::mt19937 rand_gen(device());

LightShow::LightShow() : LightShow(NUMPIXELS, PIN, NEO_GBR + NEO_KHZ800) {};

LightShow::LightShow(uint16_t numPixels, uint16_t pin, uint16_t type) {
    this->pixels = new Adafruit_NeoPixel(numPixels, pin, type);
}

LightShow::~LightShow() {
    delete this->pixels;//cleanup Adafruit_NeoPixel structure
}

void LightShow::begin() {
  pixels->begin();
}

void LightShow::solid(struct PIXEL_COLOR* (* COLOR_FUNC)(void), ADJUST_FUNC adjust_func) {
    uint8_t brightness = adjust_func(BR_MAX);
    printf("Starting LightShow::rgb adjust=%d\n",brightness);
    pixels->setBrightness(brightness);
    pixels->clear();
    for(uint16_t i=0; i < pixels->numPixels(); i++) {
        PIXEL_COLOR* c = COLOR_FUNC();
        pixels->setPixelColor(i, Adafruit_NeoPixel::Color(c->r, c->g, c->b));
    }
    pixels->show();
}

void LightShow::glowing(struct PIXEL_COLOR *c, uint16_t d, ADJUST_FUNC adjust_func) {
    printf("Starting LightShow::glowing initial delay=%dms\n",d);
    pixels->setBrightness(BR_MAX);
    pixels->clear(); // Set all pixel colors to 'off'
    for(int i=0; i < pixels->numPixels(); i++) { // For each pixel...
        pixels->setPixelColor(i,Adafruit_NeoPixel::Color(c->r, c->g, c->b));
        pixels->show();   // Send the updated pixel colors to the hardware.
        delay(DELAYVAL); // Pause before next pass through loop
    }
    //set control brightness down and up
    for(int i : range(3)) setBrightness(adjust_func(d), i % 2);
    pixels->setBrightness(BR_MAX);
}

void LightShow::setBrightness(uint16_t d, bool up) {
    br_iterator iter(up);
    printf("Starting LightShow::setBrightness up=%d",up);
    for(int i=0; i < 255 ; i++) {
        pixels->setBrightness(iter.next());
        pixels->show();
        delay(d);
    }
    printf("Ending LightShow::setBrightness level=%d\n", iter.end());
}

void LightShow::sparkle(struct PIXEL_COLOR* pixelColor, uint16_t cycles, uint32_t wait) {
    std::uniform_int_distribution<> pixels_distr(0, pixels->numPixels() - 1);
    printf("Starting LightShow::sparkle cycles=%d\n", cycles);
    for(int c = 0; c < cycles; c++) {
        for (uint16_t i = 0; i < pixels->numPixels() / 4; i++) {
            uint32_t colour = Adafruit_NeoPixel::Color(pixelColor->r, pixelColor->g, pixelColor->b);
            pixels->setPixelColor(pixels_distr(rand_gen), colour);
        }
        pixels->show();
        delay(wait);
        pixels->clear();
        pixels->show();
        delay(wait);
    }
}

void LightShow::colorWipe(struct PIXEL_COLOR* (* COLOR_FUNC)(), uint32_t wait) {
    printf("Starting LightShow::colorWipe wait=%dms\n",wait);
    for(uint16_t i=0; i<pixels->numPixels(); i++) {
        PIXEL_COLOR* color = COLOR_FUNC();
        pixels->setPixelColor(i, Adafruit_NeoPixel::Color(color->r ,color->g, color->b));
        pixels->show();
        delay(wait);
    }
}

void LightShow::theaterChase(struct PIXEL_COLOR* color, uint32_t wait) {
    for (int j=0; j<10; j++) {  //do 10 cycles of chasing
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < pixels->numPixels(); i=i+3) {
                pixels->setPixelColor(i+q, Adafruit_NeoPixel::Color(color->r, color->g, color->b));    //turn every third pixel on
            }
            pixels->show();

            delay(wait);

            for (uint16_t i=0; i < pixels->numPixels(); i=i+3) {
                pixels->setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}

void LightShow::rainbow(uint32_t wait) {
    uint16_t i, j;
    printf("Starting LightShow::rainbow wait=%dms\n",wait);
    for(j=0; j<256; j++) {
        for(i=0; i<pixels->numPixels(); i++) {
            pixels->setPixelColor(i, wheel((i+j) & 255));
        }
        pixels->show();
        delay(wait);
    }
}

void LightShow::rainbowChase(uint32_t wait) {
    uint16_t i, j;
    printf("Starting LightShow::rainbowChase wait=%dms\n",wait);
    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
        for(i=0; i< pixels->numPixels(); i++) {
            pixels->setPixelColor(i, wheel(((i * 256 / pixels->numPixels()) + j) & 255));
        }
        pixels->show();
        delay(wait);
    }
}

void LightShow::theaterChaseRainbow(uint32_t wait) {
    printf("Starting LightShow::theaterChaseRainbow wait=%dms\n",wait);
    for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < pixels->numPixels(); i=i+3) {
                pixels->setPixelColor(i+q, wheel( (i+j) % 255));    //turn every third pixel on
            }
            pixels->show();

            delay(wait);

            for (uint16_t i=0; i < pixels->numPixels(); i=i+3) {
                pixels->setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}

void LightShow::clear() const{
    pixels->clear();
    pixels->show();
}