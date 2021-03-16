# ---------------------------------------------------------------------------------------
# IDE support for headers
# ---------------------------------------------------------------------------------------
set(HAZEL_HEADERS_DIR "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE HAZEL_ENGINE_HEADERS "${HAZEL_HEADERS_DIR}/Hazel/*.hh")
file(GLOB_RECURSE HAZEL_PLATFORM_HEADERS "${HAZEL_HEADERS_DIR}/Platform/*.hh")

set(HAZEL_ALL_HEADERS "${HAZEL_ENGINE_HEADERS}"
                      "${HAZEL_PLATFORM_HEADERS}")

# TODO: Add source_group(...) functions
