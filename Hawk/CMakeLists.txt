set(SOURCE_FILES "src/Core/Application.cpp" "src/Core/log.cpp" "src/Platforms/Windows/WindowsWindow.cpp" "src/Layers/LayerStack.cpp" "src/ImGui/ImGuiLayer.cpp"  "src/Platforms/Windows/WindowsInput.cpp" "src/ImGui/ImGuiBuild.cpp" "src/Renderer/RenderAPI.cpp" "src/Platforms/Windows/Graphics.cpp" "src/Renderer/OpenGl/OpenGLBuffer.cpp" "src/Renderer/OpenGl/OpenGLVertexArray.cpp" "src/Renderer/Buffer.cpp" "src/Renderer/VertexArray.cpp" "src/Renderer/Shader.cpp" "src/Renderer/OpenGl/OpenGLRenderAPI.cpp" "src/Renderer/RenderCommand.cpp" "src/Renderer/Renderer.cpp" "src/Renderer/Camera/OrthographicCamera.cpp" "src/Core/TimeStep.cpp" "src/Renderer/OpenGl/OpenGLShader.cpp")

#TODO transform the Engine from shared to Static 
add_library (Hawk SHARED ${SOURCE_FILES})

target_include_directories(Hawk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include  
										${CMAKE_CURRENT_BINARY_DIR})

target_compile_definitions(Hawk PRIVATE HAWK_BUILD_DLL HK_ENABLE_ASSERTS)

target_precompile_headers(Hawk PRIVATE
							   include/Core/hkpch.h)

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

#GLM 
FetchContent_Declare(glm
					GIT_REPOSITORY https://github.com/g-truc/glm.git
					GIT_TAG 0.9.9.8)

FetchContent_MakeAvailable(spdlog glfw glm)

find_package(OpenGL REQUIRED)

add_subdirectory(Packages)

target_link_libraries(Hawk PUBLIC spdlog::spdlog_header_only glfw OpenGL::GL glad imgui glm)