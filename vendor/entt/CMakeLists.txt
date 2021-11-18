# This is a single file header-only library

add_library(Entt::Entt INTERFACE "include/entt/entt.hpp")

target_include_directories(Entt::Entt INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(Entt::Entt INTERFACE cxx_std_17)
