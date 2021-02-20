# file(GLOB SOURCES "*.cc")

# add_executable(Firefly "${SOURCES}")
add_library(Firefly SHARED Firefly-Core/Application.cc
                           Firefly-Core/Application.hh
                           )

target_link_libraries(Firefly PUBLIC lib_external_deps)

target_include_directories(Firefly PUBLIC ../include)
