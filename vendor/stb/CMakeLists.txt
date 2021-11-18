add_library(stb::stb STATIC stb_image.cc stb_image.h)

target_include_directories(stb::stb INTERFACE .)
