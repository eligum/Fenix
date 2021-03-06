set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_library(my_imgui STATIC "imgui.cpp"
                            "imgui_demo.cpp"
                            "imgui_draw.cpp"
                            "imgui_tables.cpp"
                            "imgui_widgets.cpp"
                            "include/imgui.h"
                            "include/imconfig.h"
                            "include/imgui_internal.h"
                            "include/imstb_rectpack.h"
                            "include/imstb_textedit.h"
                            "include/imstb_truetype.h")

target_include_directories(my_imgui PUBLIC include .)

set_property(TARGET my_imgui PROPERTY POSITION_INDEPENDENT_CODE ON)
