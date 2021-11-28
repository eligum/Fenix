file(GLOB_RECURSE _fenix_editor_SOURCES "src/*.cc")
file(GLOB_RECURSE _fenix_editor_HEADERS "src/*.hh")
# message(STATUS "fenix-editor source: ${_fenix_editor_SOURCES}")

add_executable(fenix_editor ${_fenix_editor_SOURCES} ${_fenix_editor_HEADERS})

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
