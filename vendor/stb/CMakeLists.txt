add_library(vdr_stbimg STATIC stb_image.cc stb_image.h)

target_include_directories(vdr_stbimg PUBLIC .)
