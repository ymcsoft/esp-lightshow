#include <gtest/gtest.h>
#include "../../include/utils.h"

// Assuming the isBitSet function is defined in a header file
// You would typically include the header file where isBitSet is declared
// #include "bit_utils.h"

/**
 * Check if a specific bit is set in an integer
 * @param number: the integer to check
 * @param bit_position: position of bit to check (0 = least significant bit)
 * @return: true if bit is set, false otherwise
 
bool isBitSet(int number, int bit_position) {
    return (number & (1 << bit_position)) != 0;
}*/

// Test suite for isBitSet function
TEST(IsBitSetTest, BasicFunctionality) {
    // Test number 64 = 01000000 in binary
    EXPECT_TRUE(isBitSet(64, 6));   // Bit 6 should be set
    EXPECT_FALSE(isBitSet(64, 5));  // Bit 5 should not be set
    EXPECT_FALSE(isBitSet(64, 0));  // Bit 0 should not be set

    // Test number 15 = 00001111 in binary
    EXPECT_TRUE(isBitSet(15, 0));   // Bit 0 should be set
    EXPECT_TRUE(isBitSet(15, 1));   // Bit 1 should be set
    EXPECT_TRUE(isBitSet(15, 2));   // Bit 2 should be set
    EXPECT_TRUE(isBitSet(15, 3));   // Bit 3 should be set
    EXPECT_FALSE(isBitSet(15, 4));  // Bit 4 should not be set
}

TEST(IsBitSetTest, ZeroInput) {
    // Test with zero (all bits should be unset)
    EXPECT_FALSE(isBitSet(0, 0));
    EXPECT_FALSE(isBitSet(0, 1));
    EXPECT_FALSE(isBitSet(0, 5));
    EXPECT_FALSE(isBitSet(0, 15));
}

TEST(IsBitSetTest, AllBitsSet) {
    // Test with number where all bits are set (for 8-bit: 255 = 11111111)
    EXPECT_TRUE(isBitSet(255, 0));
    EXPECT_TRUE(isBitSet(255, 1));
    EXPECT_TRUE(isBitSet(255, 2));
    EXPECT_TRUE(isBitSet(255, 3));
    EXPECT_TRUE(isBitSet(255, 4));
    EXPECT_TRUE(isBitSet(255, 5));
    EXPECT_TRUE(isBitSet(255, 6));
    EXPECT_TRUE(isBitSet(255, 7));
}

TEST(IsBitSetTest, PowersOfTwo) {
    // Test powers of 2 (single bit set)
    EXPECT_TRUE(isBitSet(1, 0));    // 1 = 00000001
    EXPECT_TRUE(isBitSet(2, 1));    // 2 = 00000010
    EXPECT_TRUE(isBitSet(4, 2));    // 4 = 00000100
    EXPECT_TRUE(isBitSet(8, 3));    // 8 = 00001000
    EXPECT_TRUE(isBitSet(16, 4));   // 16 = 00010000
    EXPECT_TRUE(isBitSet(32, 5));   // 32 = 00100000
    EXPECT_TRUE(isBitSet(64, 6));   // 64 = 01000000
    EXPECT_TRUE(isBitSet(128, 7));  // 128 = 10000000
}

TEST(IsBitSetTest, NegativeNumbers) {
    // Test with negative numbers
    EXPECT_TRUE(isBitSet(-1, 0));   // All bits set in two's complement
    EXPECT_TRUE(isBitSet(-1, 15));  // All bits set in two's complement
    EXPECT_TRUE(isBitSet(-1, 31));  // All bits set in two's complement

    // Test with negative number where only specific bits are set
    EXPECT_TRUE(isBitSet(-64, 6));  // -64 in two's complement has bit 6 set
    EXPECT_FALSE(isBitSet(-64, 5)); // -64 in two's complement has bit 5 unset
}

TEST(IsBitSetTest, EdgeCases) {
    // Test with maximum bit positions
    EXPECT_FALSE(isBitSet(1, 31));  // Bit 31 should be unset for 1
    EXPECT_TRUE(isBitSet(2147483647, 30));  // 2^31-1 has bit 30 set
    EXPECT_FALSE(isBitSet(2147483647, 31)); // 2^31-1 has bit 31 unset

    // Test with large numbers
    EXPECT_TRUE(isBitSet(1073741824, 30));  // 2^30
    EXPECT_FALSE(isBitSet(1073741824, 29)); // 2^30, bit 29 unset
}

TEST(IsBitSetTest, MixedBitPatterns) {
    // Test with mixed bit patterns
    int test_number = 171;  // 10101011 in binary
    EXPECT_TRUE(isBitSet(test_number, 0));  // Bit 0 set
    EXPECT_TRUE(isBitSet(test_number, 1)); // Bit 1 unset
    EXPECT_FALSE(isBitSet(test_number, 2));  // Bit 2 set
    EXPECT_TRUE(isBitSet(test_number, 3)); // Bit 3 unset
    EXPECT_FALSE(isBitSet(test_number, 4));  // Bit 4 set
    EXPECT_TRUE(isBitSet(test_number, 5)); // Bit 5 unset
    EXPECT_FALSE(isBitSet(test_number, 6));  // Bit 6 set
    EXPECT_TRUE(isBitSet(test_number, 7));  // Bit 7 set
}

TEST(IsBitSetTest, BoundaryConditions) {
    // Test boundary conditions
    EXPECT_FALSE(isBitSet(0, 31));  // Zero, bit 31
    EXPECT_TRUE(isBitSet(1, 0));    // One, bit 0
    EXPECT_FALSE(isBitSet(1, 1));   // One, bit 1
    EXPECT_FALSE(isBitSet(1, 31));  // One, bit 31
}

// Test to verify the specific examples from the problem
TEST(IsBitSetTest, SpecificExamples) {
    // Number 64 = 01000000 in binary
    // Bit positions: 76543210
    //                01000000
    EXPECT_FALSE(isBitSet(64, 7));  // Bit 7 should be unset
    EXPECT_TRUE(isBitSet(64, 6));   // Bit 6 should be set
    EXPECT_FALSE(isBitSet(64, 5));  // Bit 5 should be unset
    EXPECT_FALSE(isBitSet(64, 4));  // Bit 4 should be unset
    EXPECT_FALSE(isBitSet(64, 3));  // Bit 3 should be unset
    EXPECT_FALSE(isBitSet(64, 2));  // Bit 2 should be unset
    EXPECT_FALSE(isBitSet(64, 1));  // Bit 1 should be unset
    EXPECT_FALSE(isBitSet(64, 0));  // Bit 0 should be unset

    // Number 15 = 00001111 in binary
    // Bit positions: 76543210
    //                00001111
    EXPECT_FALSE(isBitSet(15, 7));  // Bit 7 should be unset
    EXPECT_FALSE(isBitSet(15, 6));  // Bit 6 should be unset
    EXPECT_FALSE(isBitSet(15, 5));  // Bit 5 should be unset
    EXPECT_FALSE(isBitSet(15, 4));   // Bit 4 should be set
    EXPECT_TRUE(isBitSet(15, 3));   // Bit 3 should be set
    EXPECT_TRUE(isBitSet(15, 2));   // Bit 2 should be set
    EXPECT_TRUE(isBitSet(15, 1));   // Bit 1 should be set
    EXPECT_TRUE(isBitSet(15, 0));   // Bit 0 should be set
}

// Test to ensure function works correctly with bit positions 0-7 for 8-bit numbers
TEST(IsBitSetTest, EightBitNumbers) {
    // Test with various 8-bit numbers
    EXPECT_FALSE(isBitSet(0, 0));   // 0 = 00000000
    EXPECT_TRUE(isBitSet(1, 0));    // 1 = 00000001
    EXPECT_TRUE(isBitSet(255, 7));  // 255 = 11111111
    EXPECT_TRUE(isBitSet(254, 7)); // 254 = 11111110
    EXPECT_TRUE(isBitSet(128, 7));  // 128 = 10000000
    EXPECT_FALSE(isBitSet(127, 7)); // 127 = 01111111
}

// Test to ensure function handles invalid bit positions gracefully
TEST(IsBitSetTest, InvalidBitPositions) {
    // These tests check behavior with bit positions beyond normal range
    // The function should work correctly with any integer bit position
    EXPECT_FALSE(isBitSet(1, 100));  // Bit 100 should be unset for 1
    EXPECT_FALSE(isBitSet(1, -1));   // Bit -1 should be unset for 1
    EXPECT_TRUE(isBitSet(1, 0));     // Bit 0 should be set for 1
}