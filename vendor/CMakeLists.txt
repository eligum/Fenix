option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLE OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_INSTALL OFF)

add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(glm)
add_subdirectory(stb)
add_subdirectory(spdlog)
add_subdirectory(entt)

set_property(TARGET spdlog PROPERTY POSITION_INDEPENDENT_CODE ON)

# ImGui
add_library(ImGui STATIC)
target_sources(
  ImGui
  PRIVATE imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp
          imgui/imgui_widgets.cpp imgui/imgui.cpp
  PRIVATE imgui/backends/imgui_impl_opengl3.cpp
          imgui/backends/imgui_impl_glfw.cpp)

target_link_libraries(
    ImGui
    PRIVATE glfw
)

target_include_directories(
  ImGui
  PUBLIC imgui
  PUBLIC imgui/backends)

# ---------------------------------------------------------------------------- #
# Group all dependencies
# ---------------------------------------------------------------------------- #

add_library(external_deps INTERFACE)
target_link_libraries(
  external_deps
  INTERFACE glfw
            glm
            glad
            stb
            spdlog
            ImGui
            entt)
