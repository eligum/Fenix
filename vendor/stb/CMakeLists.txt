add_library(stbimg STATIC stb_image.cc stb_image.h)

target_include_directories(stbimg PUBLIC .)
