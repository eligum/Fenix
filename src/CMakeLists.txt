file(GLOB MY_SOURCES "Firefly-Core/*.cc"
                     "Firefly-Core/*.hh"
                     "Events/*.hh")

add_library(Firefly SHARED ${MY_SOURCES})

target_link_libraries(Firefly PUBLIC
                               lib_external_deps
                              PRIVATE
                               project_warnings
                               project_options)

target_include_directories(Firefly PUBLIC
                                    ../include
                                   PRIVATE
                                    .)
