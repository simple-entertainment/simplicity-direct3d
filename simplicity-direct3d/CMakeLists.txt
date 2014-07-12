cmake_minimum_required(VERSION 2.8)

include(../../simplicity/simplicity/simplicity-common.cmake)

# Project
project(simplicity-direct3d)

# Policies
cmake_policy(SET CMP0015 NEW)

# Paths
file(GLOB_RECURSE SRC_FILES src/main/c++/*.cpp src/main/c++/*.h)
include_directories(../../simplicity/simplicity/src/main/c++)
include_directories(../../simplicity-winapi/simplicity-winapi/src/main/c++) # Let's try and get rid of this some time...
include_directories(dep/freeimageplus/include)
include_directories(src/main/c++)

link_directories(dep/freeimageplus/lib)

# Output
add_library(simplicity-direct3d STATIC ${SRC_FILES})

target_link_libraries(simplicity-direct3d d3d11)
target_link_libraries(simplicity-direct3d freeimageplus)
target_link_libraries(simplicity-direct3d freeimage)

