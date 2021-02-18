file(GLOB_RECURSE HEADERS
     LIST_DIRECTORIES false
     "include/*.h")

add_library(glad STATIC src/glad.c "${HEADERS}")

target_include_directories(glad PUBLIC include)
