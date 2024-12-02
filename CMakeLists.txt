cmake_minimum_required(VERSION 3.29)

project(RPG2D VERSION 1.0)

add_library(RPG2D_compiler_flags INTERFACE)
target_compile_features(RPG2D_compiler_flags INTERFACE cxx_std_20)


file(GLOB Common_SOURCES LIST_DIRECTORIES false src/Platform/*.cpp)
file(GLOB Common_HEADERS LIST_DIRECTORIES false src/Platform/*.h)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

#configure_file(RPG2DConfig.h.in RPG2DConfig.h)

add_subdirectory(src/Game)
add_subdirectory(src/Editor)
