#include "Hawk.h"
#include "glm/ext.hpp" 
#include "imgui.h"

#include "Renderer/Opengl/OpenGLShader.h"

#include "Core/EntryPoint.h"
#include "SandBox2D.h"

class ExampleLayer2 : public Hawk::Layer {

public:
	ExampleLayer2() :Layer("example1"), m_CameraController(1280.0f / 720.0f)
	{

		float dataS[] = {
		-0.25f, -0.25f, 0.0f, 0.0f, 0.0f,
		0.75f, -0.25f, 0.0f, 1.0f, 0.0f,
		0.75f, 0.75f, 0.0f,  1.0f, 1.0f,
		-0.25, 0.75 , 0.0f,  0.0f, 1.0f
		};

		unsigned int indicesS[6] = { 0, 1, 3, 3, 2, 1 };

		Hawk::Ref<Hawk::VertexBuffer> Vbuff(Hawk::VertexBuffer::Create(dataS, sizeof(dataS)));
		Vbuff->SpecifyLayout({
			{ Hawk::ShaderDataType::Float3, "a_Position" },
			{ Hawk::ShaderDataType::Float2, "a_TextureCoords"}
			});

		Hawk::Ref<Hawk::IndexBuffer> Ibuff(Hawk::IndexBuffer::Create(indicesS, sizeof(indicesS)));


		m_Vao = Hawk::Ref<Hawk::VertexArray>(Hawk::VertexArray::Create());
		m_Vao->AttachVertexBuffer(Vbuff);
		m_Vao->AttachIndexBuffer(Ibuff);

		m_Texture = Hawk::Texture2D::Create("D:\\PROJECTS\\Hawk\\Sandbox\\assets\\textures\\fire-flower-flames.png");

		m_ShaderLibrary.Load("D:\\PROJECTS\\Hawk\\Sandbox\\assets\\shaders\\gridshader.glsl", "gridshader");
		auto m_TextureShader = m_ShaderLibrary.Load("D:\\PROJECTS\\Hawk\\Sandbox\\assets\\shaders\\textureshader.glsl", "textureshader");

		std::static_pointer_cast<Hawk::OpenGLShader>(m_TextureShader)->Bind();
		std::static_pointer_cast<Hawk::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	};

	void OnUpdate(Hawk::TimeStep ts) override
	{
		//HK_TRACE("Delta Time:{}s", ts);

		m_CameraController.OnUpdate(ts);

		Hawk::RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1));
		Hawk::RenderCommand::Clear();

		Hawk::Renderer::BeginScene(m_CameraController.GetCamera());

		auto shader = m_ShaderLibrary.Get("gridshader");

		std::static_pointer_cast<Hawk::OpenGLShader>(shader)->Bind();
		std::static_pointer_cast<Hawk::OpenGLShader>(shader)->UploadUniformFloat4("u_Color", m_Color);

		m_Texture->Bind(0);
		Hawk::Renderer::Submit(m_Vao, m_ShaderLibrary.Get("textureshader"), glm::mat4(1.0f));


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.26f * j, 0.26f * i, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25));
				Hawk::Renderer::Submit(m_Vao, shader, transform);

			}

		}

		Hawk::Renderer::EndScene();

	}

	void OnImGuiRender(ImGuiContext* context) override {

		ImGui::SetCurrentContext(context);
		ImGui::Begin("Color Picker");
		ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
		ImGui::End();

	};

	void setupEvents(Hawk::EventDispatcher& dispatcher) override {

		Subscribe<Hawk::MouseScrolledEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ExampleLayer2::OnMouseScroll));
	}

	bool OnMouseScroll(Hawk::MouseScrolledEvent& event) {

		m_CameraController.OnMouseScroll(event);
		return false;
	}



private:

	Hawk::ShaderLibrary m_ShaderLibrary;
	Hawk::Ref<Hawk::VertexArray> m_Vao;

	Hawk::OrthoGraphicCameraController m_CameraController;

	Hawk::Ref<Hawk::Texture> m_Texture;
	glm::vec4 m_Color = { 0.0f, 0.0f, 0.0f, 1.0f };
};

class Sandbox : public Hawk::Application {

public:

	Sandbox() {
		//PushLayer(new ExampleLayer2());
		PushLayer(new Sandbox2D());

	}
	~Sandbox() = default;


};

Hawk::Application* Hawk::CreateApplication() {

	return new Sandbox();

}
