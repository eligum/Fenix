file(GLOB_RECURSE HEADERS
     LIST_DIRECTORIES false
     "include/*.h")

add_library(vdr_glad STATIC src/glad.c "${HEADERS}")

target_include_directories(vdr_glad PUBLIC include)
