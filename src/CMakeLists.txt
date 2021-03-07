file(GLOB_RECURSE _hazel_SOURCE "Hazel-Core/*.cc")

# This line is just a flex of my cmake skills
list(APPEND _hazel_SOURCE "ImGui/ImGuiBuild.cc")

if(HAZEL_BUILD_SHARED)
    add_library(Hazel SHARED ${_hazel_SOURCE})
else()
    add_library(Hazel STATIC ${_hazel_SOURCE})
endif()

target_link_libraries(Hazel PUBLIC
                               external_deps
                              PRIVATE
                               my_compile_warnings
                               my_compile_features)

target_include_directories(Hazel PUBLIC ../include)
