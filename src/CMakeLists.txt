file(GLOB SOURCES "*.cc")
message("${SOURCES}")
add_executable(Firefly "${SOURCES}")

target_link_libraries(Firefly PRIVATE lib_external_deps)

# target_include_directories()

# target_compile_options()
