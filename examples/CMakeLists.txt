file(GLOB _example_SOURCES "src/*.cc")

add_executable(sandbox ${_example_SOURCES})

target_link_libraries(sandbox PRIVATE Fenix)
