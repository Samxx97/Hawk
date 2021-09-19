project("Stb_img" LANGUAGES C)

add_library(stb_img STATIC stb_image.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/)


target_include_directories(stb_img PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)