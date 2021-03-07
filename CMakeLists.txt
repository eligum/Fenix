# ---------------------------------------------------------------------------- #
#                                CMAKE ROOT FILE                               #
# ---------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.16)

## Establish project ##

project(OpenGL VERSION 1.0
        DESCRIPTION "Basic framework for easy OpenGL development"
        LANGUAGES CXX C)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/ProjectSettings.cmake)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(my_compile_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(my_compile_warnings)

# Link this 'library' to binaries you want to build using c++17 standard
add_library(my_compile_features INTERFACE)
target_compile_features(my_compile_features INTERFACE cxx_std_17)

# Bunch of options
option(HAZEL_BUILD_EXAMPLES "Build a set of example applications using Hazel" ON)
option(HAZEL_BUILD_DOCS "Build Hazel documentation, requires doxygen" OFF)
option(HAZEL_BUILD_SHARED "Build Hazel as a shared library" OFF)

## Dependencies ##

add_subdirectory(vendor)

## Build project targets ##

add_subdirectory(src)

## Complementary stuff ##

if(HAZEL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(HAZEL_BUILD_DOCS)
    # set(DOXYGEN_SKIP_DOT TRUE)
    find_package(Doxygen REQUIRED)
    add_subdirectory(docs)
endif()
