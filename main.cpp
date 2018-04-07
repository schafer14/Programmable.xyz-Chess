#include <iostream>


#include <Bitboard.h>

int main(int argc, char* argv[]) {
    // Demo usage for the Bitboard library.
    bb::Bitboard bb = 0x00E304080810E300;

    bb::printBitboard(bb);

    return 0;
}