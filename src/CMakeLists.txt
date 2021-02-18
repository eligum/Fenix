file(GLOB SOURCES "*.cc")

add_library(Firefly SHARED "${SOURCES}")

target_link_libraries(Firefly PRIVATE lib_external_deps)

target_include_directories(Firefly PUBLIC ../include)
