file(GLOB _example_SOURCES "src/*.cc")

# find_library(spdlog
#              NAMES spdlog
#              PATHS "$HOME/.local/lib"
#              REQUIRED)

add_executable(sandbox ${_example_SOURCES})

target_link_libraries(sandbox PRIVATE Firefly "~/.local/lib/libspdlog.so")

target_include_directories(sandbox PRIVATE "~/.local/include")
