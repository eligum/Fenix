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
include(cmake/CompilerWarnings.cmake)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

# Link this 'library' to binaries you want to build using c++17 standard
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Very basic PCH example
# This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
# consider breaking this out per project as necessary
option(MY_ENABLE_PCH "Enable Precompiled Headers" OFF)
if(MY_ENABLE_PCH)
    target_precompile_headers(
         project_options
        INTERFACE
         <vector>
         <string>
         <sstream>
         <unordered_map>
         <utility>)
endif()

## Dependencies ##

add_subdirectory(vendor)

## Build project targets ##

add_subdirectory(src)
add_subdirectory(examples)
