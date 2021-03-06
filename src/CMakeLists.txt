file(GLOB_RECURSE MY_SOURCES "Firefly-Core/*.cc"
                             "OpenGL/*.cpp")

add_library(Firefly STATIC ${MY_SOURCES})

target_link_libraries(Firefly PUBLIC
                               lib_external_deps
                              PRIVATE
                               project_warnings
                               project_options)

target_include_directories(Firefly PUBLIC
                                    ../include
                                   PRIVATE
                                    .)
