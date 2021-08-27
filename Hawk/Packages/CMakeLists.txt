project ("Packages" LANGUAGES CXX)

#glad
add_subdirectory(glad)

#imgui
add_library(imgui STATIC "imgui/imconfig.h"
						 "imgui/imgui.h"
						 "imgui/imgui.cpp"
						 "imgui/imgui_draw.cpp"
						 "imgui/imgui_internal.h"
						 "imgui/imgui_widgets.cpp"
						 "imgui/imstb_rectpack.h"
						 "imgui/imstb_textedit.h"
						 "imgui/imstb_truetype.h"
						 "imgui/imgui_demo.cpp"
						 "imgui/imgui_tables.cpp")

list(APPEND imgui_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

target_include_directories(imgui PUBLIC ${imgui_INCLUDE_DIRS})
