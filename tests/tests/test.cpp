//
// Created by banner on 7/04/18.
//


#include <gtest/gtest.h>

#include <Bitboard.h>


TEST(bitboardTests, popCount) {
    ASSERT_EQ(0, bb::popCount(0x00));

    ASSERT_EQ(1, bb::popCount(0x01));
    ASSERT_EQ(1, bb::popCount(0x80));
    ASSERT_EQ(1, bb::popCount(0x8000000000000000));
    ASSERT_EQ(1, bb::popCount(0x0100000000000000));
    ASSERT_EQ(1, bb::popCount(0x0000020000000000));

    ASSERT_EQ(2, bb::popCount(0x03));
    ASSERT_EQ(2, bb::popCount(0x30));
    ASSERT_EQ(2, bb::popCount(0x8000000000000001));

    ASSERT_EQ(8, bb::popCount(0xFF));
    ASSERT_EQ(8, bb::popCount(0xFF00000000000000));

    ASSERT_EQ(64, bb::popCount(0xFFFFFFFFFFFFFFFF));
}

TEST(bitboardTests, reverse) {
    ASSERT_EQ(0x8000000000000000, bb::reverse(0x01));
    ASSERT_EQ(0x01, bb::reverse(0x8000000000000000));

    ASSERT_EQ(0b0000000011000111000010000001000000010000001000001100011100000000, bb::reverse(0x00E304080810E300));
    ASSERT_EQ(0x00E304080810E300, bb::reverse(0b0000000011000111000010000001000000010000001000001100011100000000));
}

TEST(bitboardTests, bitScanForward) {
    ASSERT_EQ(0, bb::bitScanForward(0x01));
    ASSERT_EQ(0, bb::bitScanForward(0xFF));
    ASSERT_EQ(8, bb::bitScanForward(0xFF00));
    ASSERT_EQ(63, bb::bitScanForward(0x8000000000000000));
    ASSERT_EQ(7, bb::bitScanForward(0x80));
}

TEST(bitboardTests, pop) {
    ASSERT_EQ(0, bb::pop(0x8000));

    ASSERT_EQ(0xFE000000000000, bb::pop(0xFF000000000000));

    ASSERT_EQ(0x80000300, bb::pop(0x80000310));
}