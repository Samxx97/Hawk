set(SOURCE_FILES "src/core/Application.cpp" "src/core/log.cpp" "src/core/Platforms/AnyPlatformWindow.cpp")

add_library (Hawk SHARED ${SOURCE_FILES})

target_include_directories(Hawk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include  
										${CMAKE_CURRENT_BINARY_DIR})

target_compile_definitions(Hawk PRIVATE HAWK_BUILD_DLL HK_ENABLE_ASSERTS)

include(GenerateExportHeader)

generate_export_header(Hawk 
			EXPORT_MACRO_NAME HAWK_API
			EXPORT_FILE_NAME  hawk_exports.h)


#dependencies:
include(FetchContent)

#spdlog library
FetchContent_Declare(spdlog
					 GIT_REPOSITORY https://github.com/gabime/spdlog.git
					 GIT_TAG  v1.8.5)


#GLFW library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(glfw
					GIT_REPOSITORY https://github.com/glfw/glfw.git
					GIT_TAG 3.3.4)



FetchContent_MakeAvailable(spdlog glfw)




target_link_libraries(Hawk PUBLIC spdlog::spdlog_header_only glfw)