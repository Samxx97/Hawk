#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

#include "Renderer/VertexArray.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Opengl/OpenGLShader.h"
#include "Renderer/Camera/OrthographicCamera.h"

namespace Hawk {

	Renderer::SceneData* Renderer::m_Data = new Renderer::SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}
	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		m_Data->ViewProjection = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		std::static_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_Data->ViewProjection);
		std::static_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}


}