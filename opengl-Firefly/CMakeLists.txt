# Build all dependencies

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLE OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

add_subdirectory(vendor/glad)

add_subdirectory(vendor/stb)

# add_subdirectory(vendor/glm)





if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")
endif()

add_library("${PROJECT_NAME}" )
