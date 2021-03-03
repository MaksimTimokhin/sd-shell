cmake_minimum_required(VERSION 3.14)
project(sd-shell)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_FILES "src/*/*.cpp")
file(GLOB_RECURSE TEST_SRC_FILES "test/*.cpp")

add_subdirectory(src)
add_subdirectory(test)