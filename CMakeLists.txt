cmake_minimum_required(VERSION 3.12)

project(OpenGL VERSION 1.0
        DESCRIPTION "Basic framework for easy OpenGL development"
        LANGUAGES CXX C)

# Build framework library
add_subdirectory(opengl-Firefly)

# Build framework executable
add_subdirectory(opengl-Sandbox)
