cmake_minimum_required(VERSION 3.10)
project(XSFML)

set(CMAKE_CXX_STANDARD 11)

file(GLOB FILES *)
add_library(XSFML ${FILES})

add_executable(foo foo.cpp) # dummy exe for testing