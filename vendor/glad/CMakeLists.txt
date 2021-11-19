add_library(glad STATIC "src/glad.c"
                        "include/glad/glad.h"
                        "include/KHR/khrplatform.h")

target_include_directories(glad PUBLIC include)
# set_property(TARGET Glad::Glad PROPERTY POSITION_INDEPENDENT_CODE ON)
