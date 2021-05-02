set(SOURCE_FILES "src/core/Application.cpp" "src/core/log.cpp")

add_library (Hawk SHARED ${SOURCE_FILES})

target_include_directories(Hawk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include  
										${CMAKE_CURRENT_BINARY_DIR})

target_compile_definitions(Hawk PRIVATE HAWK_BUILD_DLL )

include(GenerateExportHeader)

generate_export_header(Hawk 
			EXPORT_MACRO_NAME HAWK_API
			EXPORT_FILE_NAME  hawk_exports.h)


include(FetchContent)


FetchContent_Declare(spdlog
					 GIT_REPOSITORY https://github.com/gabime/spdlog.git
					 GIT_TAG  v1.8.5)


FetchContent_MakeAvailable(spdlog)

target_link_libraries(Hawk PUBLIC spdlog::spdlog_header_only)





