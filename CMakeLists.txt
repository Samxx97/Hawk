cmake_minimum_required (VERSION 3.18)
project ("Hawk" LANGUAGES CXX)


#setting the default visibility
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)


#setting the output artifacts destinations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

#global definitions to all targets
add_compile_definitions($<$<PLATFORM_ID:Windows>:HAWK_PLATFORM_WINDOWS>)
add_compile_definitions($<$<CONFIG:DEBUG>:HAWK_DEBUG> $<$<CONFIG:RELEASE>:HAWK_DIST> $<$<CONFIG:RELWITHDEBINFO>:HAWK_RELEASE>)

add_subdirectory (Hawk)
add_subdirectory (Sandbox)


