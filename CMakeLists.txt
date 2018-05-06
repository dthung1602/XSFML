cmake_minimum_required(VERSION 3.10)
project(XSFML)

set(CMAKE_CXX_STANDARD 11)

include_directories(BEFORE SYSTEM include)

file(GLOB FILES include/* src/*)
add_library(XSFML ${FILES} include/XSFML/Exception.h)

add_executable(foo test/foo.cpp ) # dummy exe for testing
target_link_libraries(foo sfml-graphics sfml-window sfml-system  sfml-audio sfml-network)