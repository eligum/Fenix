# Prints the value of all the variables passed
function(print)
    foreach(var IN LISTS "${ARGN}")
        message("${var} = ${${var}}")
    endforeach()
endfunction()

# find_package(Git QUIET)
# if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#     # Update submodules as needed
#     option(GIT_SUBMODULE "Check submodules during build" ON)
#     if(GIT_SUBMODULE)
#         message(STATUS "Updating submodules")
#         execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive)
#         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#         RESULT_VARIABLE GIT_SUBMOD_RESULT)
#     if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#         message(FATAL_ERROR
#             "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
#     endif()
# endif()
# endif()

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

# Get hazel version from include/Hazel/version.h and put it in HAZEL_VERSION
function(hazel_extract_version)
    file(READ "${CMAKE_CURRENT_LIST_DIR}/include/Hazel/version.hh" file_contents)

    string(REGEX MATCH "HAZEL_VER_MAJOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number from Hazel/version.hh")
    endif()
    set(ver_major ${CMAKE_MATCH_1})

    string(REGEX MATCH "HAZEL_VER_MINOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract minor version number from Hazel/version.hh")
    endif()
    set(ver_minor ${CMAKE_MATCH_1})

    string(REGEX MATCH "HAZEL_VER_PATCH ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract patch version number from Hazel/version.hh")
    endif()
    set(ver_patch ${CMAKE_MATCH_1})

    set(HAZEL_VERSION_MAJOR ${ver_major} PARENT_SCOPE)
    set(HAZEL_VERSION_MINOR ${ver_minor} PARENT_SCOPE)
    set(HAZEL_VERSION_PATCH ${ver_patch} PARENT_SCOPE)
    set(HAZEL_VERSION "${ver_major}.${ver_minor}.${ver_patch}" PARENT_SCOPE)
endfunction()

# Enable address sanitizer (gcc/clang only)
function(hazel_enable_sanitizer target_name)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(FATAL_ERROR "Sanitizer supported only for gcc/clang")
    endif()
    message(STATUS "Address sanitizer enabled")
    target_compile_options(${target_name} PRIVATE -fsanitize=address,undefined)
    target_compile_options(${target_name} PRIVATE -fno-sanitize=signed-integer-overflow)
    target_compile_options(${target_name} PRIVATE -fno-sanitize-recover=all)
    target_compile_options(${target_name} PRIVATE -fno-omit-frame-pointer)
    target_link_libraries(${target_name} PRIVATE -fsanitize=address,undefined -fuse-ld=gold)
endfunction()