file(GLOB_RECURSE MY_SOURCES "Firefly-Core/*.cc"
                             "ImGui/*.cc")

if(HAZEL_BUILD_SHARED)
    add_library(Hazel SHARED ${MY_SOURCES})
else()
    add_library(Hazel STATIC ${MY_SOURCES})
endif()

target_link_libraries(Hazel PUBLIC
                               external_deps
                              PRIVATE
                               my_compile_warnings
                               my_compile_features)

target_include_directories(Hazel PUBLIC ../include)
