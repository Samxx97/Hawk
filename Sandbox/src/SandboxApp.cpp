#include "Hawk.h"
#include "glm/ext.hpp" 
#include "imgui.h"

#include "Renderer/Opengl/OpenGLShader.h"

class ExampleLayer2 : public Hawk::Layer {

public:
	ExampleLayer2() :Layer("example1"), m_Camera(-1.6f, 1.6f, 0.9f, -0.9f)
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

		m_shader = Hawk::Ref<Hawk::Shader>(Hawk::Shader::Create("D:\\PROJECTS\\Hawk\\Sandbox\\assets\\shaders\\gridshader.glsl"));
		m_TextureShader = Hawk::Shader::Create("D:\\PROJECTS\\Hawk\\Sandbox\\assets\\shaders\\textureshader.glsl");

		m_Texture = Hawk::Texture2D::Create("D:\\PROJECTS\\Hawk\\Sandbox\\assets\\textures\\fire-flower-flames.png");

		std::static_pointer_cast<Hawk::OpenGLShader>(m_TextureShader)->Bind();
		std::static_pointer_cast<Hawk::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	};

	void OnUpdate(Hawk::TimeStep ts) override
	{
		HK_TRACE("Delta Time:{}s", ts);

		if (Hawk::Input::IsKeyPressed(HK_KEY_A))
			m_CameraPosition.x -= m_CameraSpeedMovement * ts;

		else if (Hawk::Input::IsKeyPressed(HK_KEY_D))
			m_CameraPosition.x += m_CameraSpeedMovement * ts;

		if (Hawk::Input::IsKeyPressed(HK_KEY_S))
			m_CameraPosition.y -= m_CameraSpeedMovement * ts;

		else if (Hawk::Input::IsKeyPressed(HK_KEY_W))
			m_CameraPosition.y += m_CameraSpeedMovement * ts;

		if (Hawk::Input::IsKeyPressed(HK_KEY_M))
			m_CameraRotation -= m_CameraSpeedRotation * ts;

		else if (Hawk::Input::IsKeyPressed(HK_KEY_N))
			m_CameraRotation += m_CameraSpeedRotation * ts;


		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);


		Hawk::RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1));
		Hawk::RenderCommand::Clear();



		Hawk::Renderer::BeginScene(m_Camera);

		std::static_pointer_cast<Hawk::OpenGLShader>(m_shader)->Bind();
		std::static_pointer_cast<Hawk::OpenGLShader>(m_shader)->UploadUniformFloat4("u_Color", m_Color);


		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.26f * j, 0.26f * i, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25));
				Hawk::Renderer::Submit(m_Vao, m_shader, transform);


			}

		}

		m_Texture->Bind(0);
		Hawk::Renderer::Submit(m_Vao, m_TextureShader, glm::mat4(1.0f));

		Hawk::Renderer::EndScene();

	}

	void OnImGuiRender(ImGuiContext* context) override {

		ImGui::SetCurrentContext(context);
		ImGui::Begin("Color Picker");
		ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
		ImGui::End();

	};

	void setupEvents(Hawk::EventDispatcher& dispatcher) override {

		//Subscribe<Hawk::MouseMovedEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ExampleLayer2::onMouseMoveEvent));
	}

	bool onMouseMoveEvent(Hawk::MouseMovedEvent& event) {

	}

private:


	Hawk::Ref<Hawk::VertexArray> m_Vao;
	Hawk::Ref<Hawk::Shader> m_shader, m_TextureShader;

	Hawk::OrthographicCamera m_Camera;
	Hawk::Ref<Hawk::Texture> m_Texture;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraSpeedMovement = 5.0f;

	float m_CameraRotation = 0;
	float m_CameraSpeedRotation = 80.0f;

	glm::vec4 m_Color = { 0.0f, 0.0f, 0.0f, 1.0f };
};

class Sandbox : public Hawk::Application {

public:

	Sandbox() {
		PushLayer(new ExampleLayer2());

	}
	~Sandbox() = default;


};

Hawk::Application* Hawk::CreateApplication() {

	return new Sandbox();

}
