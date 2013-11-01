cmake_minimum_required(VERSION 2.8)

project(jvmtoy)
set(PACKAGE_VERSION "0.0.0")

include(FindPkgConfig)
include(FindDoxygen)
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckVariableExists)
include(CheckTypeSize)
include(CheckLibraryExists)
include(CheckCSourceCompiles)
include(CMakeDetermineCCompiler)

add_definitions(-Wall -Wno-variadic-macros)
add_definitions(-DXOPEN_SOURCE=600)
add_definitions(-DGNU_SOURCE)
add_definitions(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGE_FILES)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#configure_file(
#	${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.cmake
#	${CMAKE_CURRENT_BINARY_DIR}/src/config.h)

add_subdirectory(src)
