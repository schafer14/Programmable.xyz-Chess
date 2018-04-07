cmake_minimum_required(VERSION 3.9)
project(chess)

set(CMAKE_CXX_STANDARD 17)

set (SOURCE_FILES main.cpp)
add_executable(chess_run ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(chess_run chess)