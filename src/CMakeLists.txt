file(GLOB _hazel_SOURCE LIST_DIRECTORIES false "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")
file(GLOB_RECURSE _hazel_ALL_HEADERS "${CMAKE_SOURCE_DIR}/include/*.hh")

# This line is just a flex of my cmake skills
# list(APPEND _hazel_SOURCE "ImGui/ImGuiBuild.cc;ImGui/ImGuiLayer.cc")

if(HAZEL_BUILD_SHARED)
    add_library(Hazel SHARED ${_hazel_SOURCE} ${_hazel_ALL_HEADERS})
else()
    add_library(Hazel STATIC ${_hazel_SOURCE} ${_hazel_ALL_HEADERS})
endif()

target_link_libraries(Hazel PUBLIC
                              external_deps
                            PRIVATE
                              my_compile_warnings
                              my_compile_features)

target_include_directories(Hazel PUBLIC "${CMAKE_SOURCE_DIR}/include")
