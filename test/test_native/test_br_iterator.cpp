//
// Created by Yuri Moiseyenko on 2025-12-18.
//

#if !defined(ARDUINO)
#include "include/types.h"
#endif

#include "br_iterator.h"
#include <gtest/gtest.h>
// uncomment line below if you plan to use GMock
// #include <gmock/gmock.h>

TEST(BRIterator, BeginEndUp) {
    br_iterator it(true);
    EXPECT_EQ(it.begin(), BR_MIN);
    EXPECT_EQ(it.end(), BR_MAX);
}

TEST(BRIterator, IterateUp) {
    br_iterator it(true);
    for (int i = BR_MIN; i <= BR_MAX; ++i) {
        uint8_t v = it.next();
        EXPECT_EQ(v, static_cast<uint8_t>(i));
    }
    // once at or past end, next() should stay at BR_MAX
    EXPECT_EQ(it.next(), BR_MAX);
}

TEST(BRIterator, BeginEndDown) {
    br_iterator it(false);
    EXPECT_EQ(it.begin(), BR_MAX);
    EXPECT_EQ(it.end(), BR_MIN);
}

TEST(BRIterator, IterateDown) {
    br_iterator it(false);
    for (int i = BR_MAX; i >= BR_MIN; --i) {
        uint8_t v = it.next();
        EXPECT_EQ(v, static_cast<uint8_t>(i));
    }
    // once below begin, next() should stay at BR_MIN
    EXPECT_EQ(it.next(), BR_MIN);
}