cmake_minimum_required(VERSION 3.12)

project(OpenGL VERSION 1.0
        DESCRIPTION "Basic framework for easy OpenGL development"
        LANGUAGES CXX C)

# Build framework library
add_subdirectory(opengl-Firefly)

# Build framework executable
add_subdirectory(opengl-Sandbox)

# ----------------------------------------------------------------------- #

cmake_minimum_required(VERSION 3.14)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")

## Establish project ##

project(OpenGL VERSION 1.0
        DESCRIPTION "Basic framework for easy OpenGL development"
        LANGUAGES CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin-${PROJECT_NAME}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin-${PROJECT_NAME}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin-${PROJECT_NAME}")

## Dependencies ##

add_subdirectory()

## Build app ##

add_subdirectory(src)
