#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Camera/OrthographicCamera.h"
#include "Renderer/Shader.h"

namespace Hawk {

	Renderer::SceneData* Renderer::m_Data = new Renderer::SceneData();

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		m_Data->ViewProjection = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadeUniform(m_Data->ViewProjection, "u_VP");
		shader->UploadeUniform(transform, "u_Transform");

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}


}