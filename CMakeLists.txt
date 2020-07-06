cmake_minimum_required(VERSION 3.10)

project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO: Find include dir programmatically
set(SDL2_INCLUDE_DIR /usr/include/SDL2)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp src/*.h)

add_executable(main ${sources})
target_compile_options(main PUBLIC --std=c++17 -g -Wall -x c++)
target_link_libraries(main SDL2)
target_include_directories(main PUBLIC ${SDL2_INCLUDE_DIR})
