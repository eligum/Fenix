# Prints the value of all the variables passed
function(print)
    foreach(var IN LISTS "${ARGN}")
        message("${var} = ${${var}}")
    endforeach()
endfunction()

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Updating submodules")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive)
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR
            "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
    endif()
endif()
endif()

function(enable_doxygen)
    option(ENABLE_DOXYGEN "Enable doxygen doc builds of source" OFF)
    if(ENABLE_DOXYGEN)
        set(DOXYGEN_CALLER_GRAPH YES)
        set(DOXYGEN_CALL_GRAPH YES)
        set(DOXYGEN_EXTRACT_ALL YES)
        set(DOXYGEN_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/docs")
        find_package(Doxygen REQUIRED dot)
        doxygen_add_docs(doxygen-docs ${PROJECT_SOURCE_DIR})
    endif()
endfunction()
