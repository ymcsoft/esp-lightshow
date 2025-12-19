//
// Created by Yuri Moiseyenko on 2025-12-18.
//

#ifndef ESP_LIGHTSHOW_TYPES_H
#define ESP_LIGHTSHOW_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct PIXEL_COLOR {
    uint8_t r, g, b;
    explicit PIXEL_COLOR(uint8_t r=0, uint8_t g=0, uint8_t b=0) {
        this->r = r;
        this->b = b;
        this->g = g;
    }
};

#endif //ESP_LIGHTSHOW_TYPES_H