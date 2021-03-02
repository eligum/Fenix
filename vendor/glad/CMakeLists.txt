file(GLOB_RECURSE _glad_HEADERS
     LIST_DIRECTORIES false
     "include/*.h")

add_library(glad STATIC src/glad.c "${_glad_HEADERS}")

set_property(TARGET glad PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(glad PUBLIC include)
