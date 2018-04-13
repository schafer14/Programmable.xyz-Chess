//
// Created by banner on 7/04/18.
//

#ifndef CHESS_BITBOARD_H
#define CHESS_BITBOARD_H

#include <stdint-gcc.h>

namespace bb {
    typedef uint_fast64_t Bitboard;

    Bitboard straightMoves(Bitboard, Bitboard);
    Bitboard diagonalMoves(Bitboard, Bitboard);

    void printBitboard(Bitboard);
    void printBinary(Bitboard);
    void printHex(Bitboard);

    int bitScanForward(Bitboard);
    int popCount(Bitboard);
    Bitboard reverse(Bitboard);
    Bitboard pop(Bitboard);
}



#endif //CHESS_BITBOARD_H
