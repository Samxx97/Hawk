#include "Hawk.h"

#include "imgui.h"

class ExampleLayer2 : public Hawk::Layer {

public:
	ExampleLayer2() :Layer("example1"), m_Camera(-1.6f, 1.6f, 0.9f, -0.9f)
	{

		float data[] = {
	  -0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		 0.0f,0.5f,0.0f
		};

		unsigned int indices[3] = { 0, 1, 2 };

		const std::string VertexShadersrc = R"(
						#version 330 core

						layout(location = 0) in vec3 a_Position;
						out vec3 v_Position;

						uniform mat4 u_VP;

						void main()
						{
							v_Position = a_Position;
							gl_Position = u_VP * vec4(v_Position, 1.0);
						}

					)";

		const std::string FrgmentShadersrc = R"(
						#version 330 core
						in vec3 v_Position;

						void main()
						{
							gl_FragColor = vec4(v_Position*0.5 + 0.5,1.0);

						}

				)";

		m_shaderT = std::shared_ptr<Hawk::Shader>(new Hawk::Shader(VertexShadersrc, FrgmentShadersrc));

		std::shared_ptr<Hawk::VertexBuffer> Vbuff(Hawk::VertexBuffer::Create(data, sizeof(data)));
		Vbuff->SpecifyLayout({
			{ Hawk::ShaderDataType::Float3, "a_Position" }

			});

		std::shared_ptr<Hawk::IndexBuffer> Ibuff(Hawk::IndexBuffer::Create(indices, sizeof(indices)));


		m_VaoT = std::shared_ptr<Hawk::VertexArray>(Hawk::VertexArray::Create());
		m_VaoT->AttachVertexBuffer(Vbuff);
		m_VaoT->AttachIndexBuffer(Ibuff);


		float dataS[] = {
		-0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.75f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.75f, 0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.25, 0.75 , 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		unsigned int indicesS[6] = { 0, 1, 3, 3, 2, 1 };



		const std::string VertexShadersrcS = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;
				out vec4 v_Color;

				uniform mat4 u_VP;

				void main()
				{
					v_Color = a_Color;
					gl_Position = u_VP * vec4(a_Position, 1.0);
				}

			)";

		const std::string FrgmentShadersrcS = R"(
				#version 330 core
				in vec4 v_Color;

				void main()
				{
					gl_FragColor = v_Color;

				}

		)";

		m_shaderS = std::shared_ptr<Hawk::Shader>(new Hawk::Shader(VertexShadersrcS, FrgmentShadersrcS));

		std::shared_ptr<Hawk::VertexBuffer> VbuffS(Hawk::VertexBuffer::Create(dataS, sizeof(dataS)));
		VbuffS->SpecifyLayout({
			{ Hawk::ShaderDataType::Float3, "a_Position" },
			{ Hawk::ShaderDataType::Float4, "a_Color" }

			});

		std::shared_ptr<Hawk::IndexBuffer> IbuffS(Hawk::IndexBuffer::Create(indicesS, sizeof(indicesS)));


		m_VaoS = std::shared_ptr<Hawk::VertexArray>(Hawk::VertexArray::Create());
		m_VaoS->AttachVertexBuffer(VbuffS);
		m_VaoS->AttachIndexBuffer(IbuffS);

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

		Hawk::Renderer::Submit(m_VaoS, m_shaderS);
		Hawk::Renderer::Submit(m_VaoT, m_shaderT);

		Hawk::Renderer::EndScene();

	}

	void OnImGuiRender(ImGuiContext* context) override {

		ImGui::SetCurrentContext(context);

	};

	void setupEvents(Hawk::EventDispatcher& dispatcher) override {

		//Subscribe<Hawk::MouseMovedEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ExampleLayer2::onMouseMoveEvent));
	}

	bool onMouseMoveEvent(Hawk::MouseMovedEvent& event) {

	}

private:

	std::shared_ptr<Hawk::VertexArray> m_VaoT;
	std::shared_ptr<Hawk::Shader> m_shaderT;

	std::shared_ptr<Hawk::VertexArray> m_VaoS;
	std::shared_ptr<Hawk::Shader> m_shaderS;

	Hawk::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraSpeedMovement = 5.0f;


	float m_CameraRotation = 0;
	float m_CameraSpeedRotation = 80.0f;

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
