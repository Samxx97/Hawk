set(SOURCE_FILES src/core/Application.cpp)

add_library (Hawk SHARED ${SOURCE_FILES})

target_include_directories(Hawk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include  
										${CMAKE_CURRENT_BINARY_DIR})


include(GenerateExportHeader)
generate_export_header(Hawk 
			EXPORT_MACRO_NAME HAWK_API
			EXPORT_FILE_NAME  hawk_exports.h)





