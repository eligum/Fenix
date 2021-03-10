file(GLOB HAZEL_SOURCE LIST_DIRECTORIES false "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

# This line is just a flex of my cmake skills
# list(APPEND HAZEL_SOURCE "ImGui/ImGuiBuild.cc;ImGui/ImGuiLayer.cc")

if(HAZEL_BUILD_SHARED)
    add_library(Hazel SHARED ${HAZEL_SOURCE} ${HAZEL_ALL_HEADERS})
else()
    add_library(Hazel STATIC ${HAZEL_SOURCE} ${HAZEL_ALL_HEADERS})
endif()

target_link_libraries(Hazel PUBLIC
                              external_deps
                            PRIVATE
                              my_compile_warnings
                              my_compile_features)

target_include_directories(Hazel PUBLIC "${HAZEL_HEADERS_DIR}")
