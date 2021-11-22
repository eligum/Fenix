file(GLOB _fenix_editor_SOURCES "*.cc")

add_executable(fenix_editor ${_fenix_editor_SOURCES})

target_link_libraries(fenix_editor PRIVATE
                                    Fenix
                                    my_compile_warnings
                                    my_compile_features)

# A lil' bit of cmake fancyness
add_custom_command(
    TARGET fenix_editor
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:fenix_editor>
    "${CMAKE_CURRENT_LIST_DIR}")
