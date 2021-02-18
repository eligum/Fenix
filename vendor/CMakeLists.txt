add_subdirectory(glad)

add_subdirectory(stb)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLE OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(glfw)

find_package(glm REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# ---------------------------------------------------------------------------- #

add_library(lib_external_deps INTERFACE)
target_link_libraries(lib_external_deps INTERFACE
                                        glfw3
                                        glm
                                        vdr_glad
                                        vdr_stb)
