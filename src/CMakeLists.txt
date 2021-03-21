file(GLOB FENIX_SOURCE LIST_DIRECTORIES false "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

# This line is just a flex of my cmake skills
# list(APPEND FENIX_SOURCE "ImGui/ImGuiBuild.cc;ImGui/ImGuiLayer.cc")

if(FENIX_BUILD_SHARED)
    add_library(Fenix SHARED ${FENIX_SOURCE} ${FENIX_ALL_HEADERS})
else()
    add_library(Fenix STATIC ${FENIX_SOURCE} ${FENIX_ALL_HEADERS})
endif()

target_link_libraries(Fenix PUBLIC
                              external_deps
                            PRIVATE
                              my_compile_warnings
                              my_compile_features)

target_include_directories(Fenix PUBLIC "${FENIX_HEADERS_DIR}")
