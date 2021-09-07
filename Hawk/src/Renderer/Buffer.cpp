#include "Renderer/Opengl/OpenGLBuffer.h"

#include "Renderer/RenderAPI.h"

namespace Hawk {

	VertexBuffer* VertexBuffer::Create(float* data, uint32_t size)
	{
		switch (RenderAPI::GraphicsAPI)
		{
		case RenderAPI::API::OpenGL: return new OpenGLVertexBuffer(data, size);

		case RenderAPI::API::None: HK_CORE_ASSERT(false, "no behavior is implemented for RenderAPI:None yet");
			return nullptr;
		}

		HK_CORE_ASSERT(false, "No Rendering API is Selected");
		return nullptr;

	}

	IndexBuffer* IndexBuffer::Create(uint32_t* data, uint32_t size)
	{
		switch (RenderAPI::GraphicsAPI)
		{
		case RenderAPI::API::OpenGL: return new OpenGLIndexBuffer(data, size);

		case RenderAPI::API::None: HK_CORE_ASSERT(false, "no behavior is implemented for RenderAPI:None yet");
			return nullptr;
		}

		HK_CORE_ASSERT(false, "No Rendering API is Selected");
		return nullptr;


	}

}