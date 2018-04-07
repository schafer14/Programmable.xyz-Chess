project(chess)

set(HEADER_FILES
        Bitboard.h
        )

set (SOURCE_FILES
        Bitboard.cpp
        )

add_library(chess STATIC ${SOURCE_FILES} ${HEADER_FILES})