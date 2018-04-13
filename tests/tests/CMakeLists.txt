include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicTests bitboard_test.cpp)

target_link_libraries(runBasicTests gtest gtest_main)
target_link_libraries(runBasicTests chess)