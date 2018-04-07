//
// Created by banner on 7/04/18.
//

#include "Bitboard.h"

#include <iostream>
#include <bitset>
#include <iomanip>


// Default board configurations
const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

// Indexes for bitscans https://chessprogramming.wikispaces.com/BitScan
const int index64[64] = {
        0, 47,  1, 56, 48, 27,  2, 60,
        57, 49, 41, 37, 28, 16,  3, 61,
        54, 58, 35, 52, 50, 42, 21, 44,
        38, 32, 29, 23, 17, 11,  4, 62,
        46, 55, 26, 59, 40, 36, 15, 53,
        34, 51, 20, 43, 31, 22, 10, 45,
        25, 39, 14, 33, 19, 30,  9, 24,
        13, 18,  8, 12,  7,  6,  5, 63,
};

// Letters are used to represent the columns in a chess board.
char letters [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

/**
 * printBitboard
 *
 * Prints a visual representation of a bitboard.
 *
 * @author Banner Schafer (2018)
 * @param bb bitboard to print
 * @return void
 * */
void bb::printBitboard(Bitboard bb) {
    // Print board contents
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        std::cout << BOARD_HEIGHT - i << " ";

        for (int j = 0; j < BOARD_WIDTH; j++) {
            Bitboard square = (BOARD_HEIGHT - i - 1) * BOARD_WIDTH + j;

            Bitboard bit = (Bitboard)1 << square;

            if ((bit & bb) > 0) {
                std::cout << "x ";
            } else {
                std::cout << "• ";
            }
        }

        std::cout << std::endl;
    }

    // print the letters at the bottom of the board
    std::cout << "  ";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        std::cout << letters[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * printBinary
 *
 * Prints a binary representation of a bitboard.
 *
 * @author Banner Schafer (2018)
 * @param bb bitboard to print
 * @return void
 *
 * */
void bb::printBinary(Bitboard bb) {
    std::cout << "0b" << std::bitset<64>(bb) << std::endl;
}


/**
 * printHex
 *
 * Prints a hexadecimal representation of a bitboard.
 *
 * @author Banner Schafer (2018)
 * @param bb bitboard to print
 * @return void
 *
 * */
void bb::printHex(Bitboard bb) {
    std::cout << "0x" << std::setfill('0') << std::setw(16) << std::hex << bb << std::endl;
}

/**
 * bitScanForward
 *
 * Retrieves the index of the least significant one bit in a bitboard.
 *
 * @author Kim Walisch (2012) https://chessprogramming.wikispaces.com/BitScan
 * @param bb bitboard to scan
 * @precondition bb != 0
 * @return index (0..63) of least significant one bit
 */
int bb::bitScanForward(Bitboard bb) {
    const Bitboard debruijn64 = Bitboard(0x03f79d71b4cb0a89);
    return index64[((bb ^ (bb-1)) * debruijn64) >> 58];
}

/**
 * popCount
 *
 * Returns the number of one bits in a bitboard.
 *
 * @author Banner Schafer (2018)
 * @param bb bitboard to count
 * @return number of 1 bits in bitboard
 * */
int bb::popCount(Bitboard bb) {
    std::bitset<64> bit(bb);
    return int(bit.count());
}

/**
 * pop
 *
 * Returns a bitboard with the least significan bit removed.
 *
 * @author Banner Schafer (2018)
 * @param bb bitboard to pop
 * @return bitboard without LSB
 * */
bb::Bitboard bb::pop(Bitboard bb) {
    return bb & (bb - 1);
}

template <typename T, T m, int k>
static inline T swapbits(T p) {
    T q = ((p>>k)^p)&m;
    return p^q^(q<<k);
}

/**
 * reverse
 * @author Donald Knuth https://matthewarcus.wordpress.com/2012/11/18/reversing-a-64-bit-word/
 * @param bb bitboard to reverse
 * @return reversed bitboard
 */
bb::Bitboard bb::reverse(Bitboard bb)
{
    static const uint64_t m0 = 0x5555555555555555LLU;
    static const uint64_t m1 = 0x0300c0303030c303LLU;
    static const uint64_t m2 = 0x00c0300c03f0003fLLU;
    static const uint64_t m3 = 0x00000ffc00003fffLLU;
    bb = ((bb>>1)&m0) | (bb&m0)<<1;
    bb = swapbits<uint64_t, m1, 4>(bb);
    bb = swapbits<uint64_t, m2, 8>(bb);
    bb = swapbits<uint64_t, m3, 20>(bb);
    bb = (bb >> 34) | (bb << 30);
    return bb;
}

