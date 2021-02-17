option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLE OFF)
option(GLFW_BUILD_TESTS OFF)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/stb)
# add_subdirectory(vendor/glm)

add_library(firefly )

target_compile_features(firefly PRIVATE cxx_std_17)
if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(firefly PRIVATE "-Wall -Wextra -Wshadow")
elseif(MSVC)
    target_compile_options(firefly PRIVATE "/W4")
endif()
