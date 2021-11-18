file(GLOB_RECURSE _glad_HEADERS "include/*.h")

add_library(Glad::Glad STATIC src/glad.c "${_glad_HEADERS}")

target_include_directories(Glad::Glad PUBLIC include)
# set_property(TARGET Glad::Glad PROPERTY POSITION_INDEPENDENT_CODE ON)
