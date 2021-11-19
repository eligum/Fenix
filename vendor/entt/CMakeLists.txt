# This is a single file header-only library

add_library(entt INTERFACE "include/entt/entt.hpp")

target_include_directories(entt INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(entt INTERFACE cxx_std_17)
