#include "Renderer/RenderCommand.h"
#include "Renderer/Opengl/OpenGLRenderAPI.h"

namespace Hawk {

	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RenderAPI->SetClearColor(color);
	}


	void RenderCommand::Clear()
	{
		s_RenderAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const Hawk::Ref<VertexArray>& vertexArray)
	{
		s_RenderAPI->DrawIndexed(vertexArray);

	}
}