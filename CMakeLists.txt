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
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Link this 'library' to binaries you want to build using c++17 standard
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Bunch of options
option(FLY_BUILD_EXAMPLES "Build a set of example applications using Firefly" OFF)
option(FLY_BUILD_DOCS "Build Firefly documentation, requires doxygen" ON)
option(FLY_BUILD_SHARED "Build Firefly as a shared library" OFF)

## Dependencies ##

add_subdirectory(vendor)

## Build project targets ##

add_subdirectory(src)
add_subdirectory(examples)

if (FLY_BUILD_DOCS)
    # set(DOXYGEN_SKIP_DOT TRUE)
    find_package(Doxygen REQUIRED)
    add_subdirectory(docs)
endif()
