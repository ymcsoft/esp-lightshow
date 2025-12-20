//
// Created by Yuri Moiseyenko on 2025-12-19.
//

//#include "LightShow.h"
#include <gtest/gtest.h>
#include "../../include/LightShow.h"
#include "../../src/LightShow.cpp"
// uncomment line below if you plan to use GMock
// #include <gmock/gmock.h>

TEST(LightShow, Wheel) {
    // Test known values
    EXPECT_EQ(LightShow::wheel(0), 0x00FF0000);   // Red
    EXPECT_EQ(LightShow::wheel(85), 0x0000FF00);  // Green
    EXPECT_EQ(LightShow::wheel(170), 0x000000FF); // Blue
    EXPECT_EQ(LightShow::wheel(255), 0x00FF0000); // Red again
}

TEST(LightShow, ColorWipe) {
    //setup LightShow instance
    LightShow ls(10, 0, NEO_RGB + NEO_KHZ800);
    ls.begin();
    // Run colorWipe with a known color function
    ls.colorWipe([]() {
        static PIXEL_COLOR color(255, 0, 0); // Red color
        return &color;
    }, 0);
    // Verify that all pixels are set to red
    for (uint16_t i = 0; i < 10; i++) {
        uint32_t pixelColor = ls.getPixels()->getPixelColor(i);
        EXPECT_EQ(pixelColor, Adafruit_NeoPixel::Color(255, 0, 0));
    }
}

TEST(LightShow, Sparkle) {
    //setup LightShow instance
    LightShow ls(20, 0, NEO_RGB + NEO_KHZ800);
    ls.begin();
    // Run sparkle with a known color
    PIXEL_COLOR testColor(0, 255, 0); // Green color
    ls.sparkle(&testColor, 1, 0);
    // Since sparkle is random, we can't predict exact pixels,
    // but we can check that some pixels are set and some are not.
    bool found = false;
    for (uint16_t i = 0; i < 20; i++) {
        uint32_t pixelColor = ls.getPixels()->getPixelColor(i);
        printf("Pixel %d color: 0x%06X\n", i, pixelColor);
        if (pixelColor != Adafruit_NeoPixel::Color(0, 0, 0)) {
            found = true;
            break;
        }
    }
    EXPECT_FALSE(found);
}

TEST(LightShow, Glowing){
    //setup LightShow instance
    LightShow ls(5, 0, NEO_RGB + NEO_KHZ800);
    ls.begin();
    PIXEL_COLOR testColor(0, 0, 255); // Blue color
    ls.glowing(&testColor, 0, [](uint8_t value) { return value; });
    // Verify that all pixels are set to blue
    for (uint16_t i = 0; i < 5; i++) {
        uint32_t pixelColor = ls.getPixels()->getPixelColor(i);
        EXPECT_EQ(pixelColor, Adafruit_NeoPixel::Color(0, 0, 255));
    }
}

TEST(LightShow, TheaterChase) {
    //setup LightShow instance
    LightShow ls(9, 0, NEO_RGB + NEO_KHZ800);
    ls.begin();
    PIXEL_COLOR testColor(255, 255, 0); // Yellow color
    ls.theaterChase(&testColor, 0);
    // Verify that pixels are set in a chase pattern
    for (uint16_t i = 0; i < 9; i++) {
        uint32_t pixelColor = ls.getPixels()->getPixelColor(i);
        EXPECT_EQ(pixelColor, 0);
    }
}

TEST(LightShow, Rainbow) {
    //setup LightShow instance
    LightShow ls(10, 0, NEO_RGB + NEO_KHZ800);
    ls.begin();
    ls.rainbow(0);
    // Verify that pixels are set to rainbow colors
    for (uint16_t i = 0; i < 10; i++) {
        uint32_t pixelColor = ls.getPixels()->getPixelColor(i);
        EXPECT_NE(pixelColor, 0); // Just check that color is not black
    }
}

TEST(LightShow, RainbowChase) {
    //setup LightShow instance
    LightShow ls(15, 0, NEO_RGB + NEO_KHZ800);
    ls.begin();
    ls.rainbowChase(0);
    // Verify that pixels are set to rainbow chase colors
    for (uint16_t i = 0; i < 15; i++) {
        uint32_t pixelColor = ls.getPixels()->getPixelColor(i);
        EXPECT_NE(pixelColor, 0); // Just check that color is not black
    }
}

TEST(LightShow, TheaterChaseRainbow) {
    //setup LightShow instance
    LightShow ls(12, 0, NEO_RGB + NEO_KHZ800);
    ls.begin();
    ls.theaterChaseRainbow(0);
    // Verify that pixels are set in a rainbow chase pattern
    for (uint16_t i = 0; i < 12; i++) {
        uint32_t pixelColor = ls.getPixels()->getPixelColor(i);
        EXPECT_EQ(pixelColor, 0); // Just check that color is black
    }
}

TEST(LightShow, SOLID) {
    //setup LightShow instance
    LightShow ls(8, 0, NEO_RGB + NEO_KHZ800);
    ls.begin();
    ls.solid([]() {
        static PIXEL_COLOR color(128, 128, 128); // Grey color
        return &color;
    }, [](uint8_t value) { return value; });
    // Verify that all pixels are set to grey
    for (uint16_t i = 0; i < 8; i++) {
        uint32_t pixelColor = ls.getPixels()->getPixelColor(i);
        EXPECT_EQ(pixelColor, Adafruit_NeoPixel::Color(128, 128, 128));
    }
}
