add_subdirectory(glad)

add_subdirectory(stb)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLE OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(glfw)

set(glm_DIR ${CMAKE_CURRENT_LIST_DIR}/glm/cmake/glm)
find_package(glm REQUIRED)

add_subdirectory(spdlog)
set_property(TARGET spdlog PROPERTY POSITION_INDEPENDENT_CODE ON)

add_subdirectory(imgui)

add_subdirectory(entt)

# ---------------------------------------------------------------------------- #

add_library(external_deps INTERFACE)
target_link_libraries(external_deps INTERFACE
                                    glfw
                                    glm::glm
                                    glad
                                    stb
                                    spdlog
                                    imgui
                                    EnTT)
