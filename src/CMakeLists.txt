file(GLOB SOURCES "Firefly-Core/*.cc")

add_library(Firefly SHARED ${SOURCES})

target_link_libraries(Firefly PUBLIC lib_external_deps)

target_include_directories(Firefly PUBLIC ../include)
