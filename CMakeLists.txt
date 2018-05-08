cmake_minimum_required(VERSION 3.10)
project(XSFML)

set(CMAKE_CXX_STANDARD 11)

include_directories(BEFORE SYSTEM include)

file(GLOB FILES include/* src/*)
add_library(XSFML ${FILES} include/XSFML/Exception.h include/XSFML/TextureManager.h src/TextureManager.cpp)

add_executable(foo test/foo.cpp) # dummy exe for testing
target_link_libraries(foo sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

add_executable(test_texture_manager test/texture_manager/test_texture_manager.cpp ${FILES})
target_link_libraries(test_texture_manager sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

add_executable(test_util test/util/test_open_file.cpp include/XSFML/Util.h src/Util.cpp)
target_link_libraries(test_texture_manager sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

add_executable(test_extract_resource_name test/util/test_extract_resource_name.cpp src/Util.cpp)

add_executable(test_sound_manager test/sound_manager/test_sound_manager.cpp include/XSFML/SoundManager.h src/SoundManager.cpp src/Util.cpp)
target_link_libraries(test_sound_manager sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
