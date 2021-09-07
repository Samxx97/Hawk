#include "Renderer/Opengl/OpenGLVertexArray.h"

#include "Renderer/RenderAPI.h"
#include "Core/Core.h"

namespace Hawk {

	VertexArray* VertexArray::Create()
	{
		switch (RenderAPI::GraphicsAPI)
		{
		case RenderAPI::API::OpenGL: return new OpenGLVertexArray();

		case RenderAPI::API::None: HK_CORE_ASSERT(false, "no behavior is implemented for RenderAPI:None yet");
			return nullptr;
		}

		HK_CORE_ASSERT(false, "No Rendering API is Selected!");
		return nullptr;
	}

}
