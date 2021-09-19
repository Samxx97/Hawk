#include "Renderer/RenderAPI.h"
#include "Renderer/Opengl/OpenGLTexture2D.h"

namespace Hawk {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RenderAPI::GraphicsAPI)
		{
		case RenderAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		case RenderAPI::API::None:    HK_CORE_ASSERT(false, "no behavior is implemented for RenderAPI:None yet"); return nullptr;
		}

		HK_CORE_ASSERT(false, "No Rendering API is Selected!");
		return nullptr;
	}

}