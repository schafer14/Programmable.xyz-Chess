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

TEST(bitboardTests, straightMoves) {
//    Testing without occupation bitboards.
    ASSERT_EQ(0x01010101010101FE, bb::straightMoves(0x01, 0x00));
    ASSERT_EQ(0x808080808080807F, bb::straightMoves(0x80, 0x00));

    ASSERT_EQ(0x10101010EF101010, bb::straightMoves(0x10000000, 0x00));

    ASSERT_EQ(0xFE01010101010101, bb::straightMoves(0x0100000000000000, 0x00));
    ASSERT_EQ(0x7F80808080808080, bb::straightMoves(0x8000000000000000, 0x00));

//    Testing with an occupation bitboard
    ASSERT_EQ(0x10101010EF101010, bb::straightMoves(0x10000000, 0x80000000));
    ASSERT_EQ(0x101010106F101010, bb::straightMoves(0x10000000, 0x40000000));
    ASSERT_EQ(0x101010102F101010, bb::straightMoves(0x10000000, 0x20000000));

    ASSERT_EQ(0x10EF100000, bb::straightMoves(0x10000000, 0x1000100000));
    ASSERT_EQ(0x1028100000, bb::straightMoves(0x10000000,0x1028100000));

    ASSERT_EQ(0x10101010101010EC, bb::straightMoves(0x10, 0x06));
    ASSERT_EQ(0x101010101010106E, bb::straightMoves(0x10, 0x42));

    ASSERT_EQ(0x4080808080808080, bb::straightMoves(0x8000000000000000, 0x4000000000000000));
    ASSERT_EQ(0x4080000000000000, bb::straightMoves(0x8000000000000000, 0x4080000000000000));
    ASSERT_EQ(0x4080000000000000, bb::straightMoves(0x8000000000000000, 0x4080406080FF0E0C));
}

TEST(bitboardTests, diagonalMoves) {
//    Testing without occupation bb;
    ASSERT_EQ(0x8040201008040200, bb::diagonalMoves(0x01, 0x00));
    ASSERT_EQ(0x0102040810204000, bb::diagonalMoves(0x80, 0x00));
    ASSERT_EQ(0x40201008040201, bb::diagonalMoves(0x8000000000000000, 0x00));
    ASSERT_EQ(0x02040810204080, bb::diagonalMoves(0x0100000000000000, 0x00));
    ASSERT_EQ(0x0204885000508804, bb::diagonalMoves(0x20000000, 0x00));
    ASSERT_EQ(0x0805000508102040, bb::diagonalMoves(0x020000000000, 0x00));

//    Testing with occupation bb;
    ASSERT_EQ(0x0805000508102040, bb::diagonalMoves(0x020000000000, 0x0800004000000000));
    ASSERT_EQ(0x0805000508102000, bb::diagonalMoves(0x020000000000, 0x08000040000002000));
    ASSERT_EQ(0x05000500000000, bb::diagonalMoves(0x020000000000, 0x0804000400002000));
    ASSERT_EQ(0x05000500000000, bb::diagonalMoves(0x020000000000, 0x0805000500000200));
}