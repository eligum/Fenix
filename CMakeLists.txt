# Checkout the project repo at https://github.com/eligum/OpenGL-fw

cmake_minimum_required(VERSION 3.16)

# ---------------------------------------------------------------------------------------
# Start project
# ---------------------------------------------------------------------------------------
include(cmake/PreventInSourceBuilds.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/Util.cmake)
include(cmake/Ide.cmake)

hazel_extract_version()

project(HazelEngine VERSION ${HAZEL_VERSION} LANGUAGES CXX C)
message(STATUS "Build Hazel version: ${HAZEL_VERSION}")

# ---------------------------------------------------------------------------------------
# Project build configuration
# ---------------------------------------------------------------------------------------
include(cmake/buildTypeSettings.cmake)

# Output all binaries under the same easy-to-access directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")

# Disable compiler specific extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(my_compile_warnings INTERFACE)
set_project_warnings(my_compile_warnings)

# Link this 'library' to binaries you want to build using c++17 standard
add_library(my_compile_features INTERFACE)
target_compile_features(my_compile_features INTERFACE cxx_std_17)

# Bunch of options
option(HAZEL_BUILD_EXAMPLES "Build a set of example applications using Hazel" ON)
option(HAZEL_BUILD_DOCS "Build Hazel documentation, requires doxygen" OFF)
option(HAZEL_BUILD_SHARED "Build Hazel as a shared library" OFF)

# ---------------------------------------------------------------------------------------
# Build project dependencies
# ---------------------------------------------------------------------------------------
add_subdirectory(vendor)

# ---------------------------------------------------------------------------------------
# Build project
# ---------------------------------------------------------------------------------------
add_subdirectory(src)

if(HAZEL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(HAZEL_BUILD_DOCS)
    # set(DOXYGEN_SKIP_DOT TRUE)
    find_package(Doxygen REQUIRED)
    add_subdirectory(docs)
endif()
