# ---------------------------------------------------------------------------- #
#                                CMAKE ROOT FILE                               #
# ---------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## Establish project ##

project(OpenGL VERSION 1.0
        DESCRIPTION "Basic framework for easy OpenGL development"
        LANGUAGES CXX C)

include(cmake/ProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

## Dependencies ##

add_subdirectory(vendor)

## Build project targets ##

add_subdirectory(src)
add_subdirectory(examples)
