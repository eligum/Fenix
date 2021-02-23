# Aborts with fatal error if user tried to create an in-source cmake build
function(PreventInSourceBuild)
    # make sure the user doesn't play dirty with symlinks
    get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
    get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

    # disallow in-source builds
    if("${srcdir}" STREQUAL "${bindir}")
        message("ERROR! You should not configure this project with an in-source build.")
        message("NOTE: Given that you already tried to make an in-source build, CMake")
        message("      has already created several files and directories in your source")
        message("      tree. Run 'git status' to find them and remove them.")
        message(FATAL_ERROR)
    endif()
endfunction()

PreventInSourceBuild()
