file(GLOB_RECURSE _glad_HEADERS
     LIST_DIRECTORIES false
     "include/*.h")

add_library(glad STATIC src/glad.c "${_glad_HEADERS}")

target_include_directories(glad PUBLIC include)
