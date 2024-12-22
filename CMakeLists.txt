cmake_minimum_required(VERSION 3.16)
project(cylange LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


FILE(GLOB_RECURSE headers "src/*.hpp")
FILE(GLOB_RECURSE sources "src/*.cpp")

add_executable(game ${sources} ${headers})


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${sources} ${headers})
