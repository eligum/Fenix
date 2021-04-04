# This is a single file header-only library

add_library(EnTT INTERFACE "include/entt/entt.hpp")

target_include_directories(EnTT INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(EnTT PUBLIC my_compile_features)
