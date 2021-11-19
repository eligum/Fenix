add_library(stb STATIC stb_image.cc stb_image.h)

target_include_directories(stb INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
