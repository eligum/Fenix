file(GLOB _fenix_editor_SOURCES "*.cc")

add_executable(fenix_editor ${_fenix_editor_SOURCES})

target_link_libraries(fenix_editor PRIVATE
                                    Fenix
                                    my_compile_warnings
                                    my_compile_features)
