# NOTE: The order of this list determines the order of items in the Guides
#       (i.e. Pages) list in the generated documentation

set(BOX2D_DOXYGEN_SOURCES
    "include/Fenix"
    "docs/overview.md"
    "docs/common.md")

# Format the source list into a Doxyfile INPUT value that Doxygen can parse
foreach(path IN LISTS BOX2D_DOXYGEN_SOURCES)
    set(BOX2D_DOXYGEN_INPUT "${BOX2D_DOXYGEN_INPUT} \\\n\"${CMAKE_SOURCE_DIR}/${path}\"")
endforeach()

# https://cmake.org/cmake/help/latest/command/configure_file.html
configure_file(Doxyfile.in Doxyfile @ONLY)

add_custom_target(docs ALL "${DOXYGEN_EXECUTABLE}"
                  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/docs"
                  COMMENT "Generating HTML documentation" VERBATIM)

# install(DIRECTORY "${CMAKE_BINARY_DIR}/docs/html"
#         DESTINATION "${CMAKE_INSTALL_DOCDIR}")
