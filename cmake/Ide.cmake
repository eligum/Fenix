# ---------------------------------------------------------------------------------------
# IDE support for headers
# ---------------------------------------------------------------------------------------
set(FENIX_HEADERS_DIR "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE FENIX_ENGINE_HEADERS "${FENIX_HEADERS_DIR}/Fenix/*.hh")
file(GLOB_RECURSE FENIX_PLATFORM_HEADERS "${FENIX_HEADERS_DIR}/Platform/*.hh")

set(FENIX_ALL_HEADERS "${FENIX_ENGINE_HEADERS}"
                      "${FENIX_PLATFORM_HEADERS}")

# TODO: Add source_group(...) functions
