cmake_minimum_required(VERSION 3.12)
project(Prelude VERSION 1.0
                DESCRIPTION "Basic framework for easy OpenGL development"
                LANGUAGES CXX C)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLE OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")
    # set(GLAD_LIBRARIES dl)
endif()

include_directories(Prelude/include/
                    Prelude/vendor/glad/include/
                    Prelude/vendor/glfw/include/
                    Prelude/vendor/glm/
                    Prelude/vendor/stb/)

add_executable("${PROJECT_NAME}" )
