//
// Created by Yuri Moiseyenko on 2025-12-18.
//
#include "range.h"
#include <gtest/gtest.h>
#include <vector>

TEST(RangeTest, SingleArgInclusive) {
    range r(4);
    std::vector<int> got;
    for (int v : r) got.push_back(v);
    std::vector<int> want = {0, 1, 2, 3};
    EXPECT_EQ(got, want);
}

TEST(RangeTest, StartEndInclusive) {
    range r(2, 5);
    std::vector<int> got;
    for (int v : r) got.push_back(v);
    std::vector<int> want = {2, 3, 4};
    EXPECT_EQ(got, want);
}

TEST(RangeTest, StartGreaterThanEndIsEmpty) {
    range r(5, 2);
    std::vector<int> got;
    for (int v : r) got.push_back(v);
    std::vector<int> want = {};
    EXPECT_EQ(got, want);
}
