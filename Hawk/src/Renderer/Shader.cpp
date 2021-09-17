#include "Renderer/RenderAPI.h"
#include "Renderer/Opengl/OpenGLShader.h"
#include "Core/Core.h"

namespace Hawk {

	Shader* Shader::Create(const std::string& vertexsrc, const std::string& fragmentsrc)
	{
		switch (RenderAPI::GraphicsAPI)
		{
		case RenderAPI::API::OpenGL: return new OpenGLShader(vertexsrc, fragmentsrc);

		case RenderAPI::API::None: HK_CORE_ASSERT(false, "no behavior is implemented for RenderAPI:None yet"); return nullptr;

		}

		HK_CORE_ASSERT(false, "No Rendering API is Selected!");
		return nullptr;

	}

}