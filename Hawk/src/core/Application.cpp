#include "Core/Application.h"
#include "Core/Core.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "ImGui/ImGuiLayer.h"

namespace Hawk {

	Application* Application::s_Instance = nullptr;


	Application::Application() : m_Camera(-1.6f, 1.6f, 0.9f, -0.9f)
	{
		Init();
	}

	void Application::Run()
	{

		m_LayerStack.SetupEvents(m_EventDispatcher);

		while (m_Running) {

			RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1));
			RenderCommand::Clear();

			m_Camera.SetRotation(45.0f);
			m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_VaoS, m_shaderS);
			Renderer::Submit(m_VaoT, m_shaderT);

			Renderer::EndScene();


			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender(m_ImGuiLayer->m_context);
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}


	void Application::Init() {

		HK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		Log::init();
		HK_CORE_TRACE("Initializing Application");

		m_Window = std::unique_ptr<Window>(Window::Create(m_EventDispatcher));
		Input::setInput(m_Window->GetInput());

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		//Register Application EventHandlers
		m_EventDispatcher.Subscribe<WindowCloseEvent>(BIND_EVENT_FN_DEFAULT(Application::OnWindowClosedEvent));


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

		m_shaderT = std::shared_ptr<Shader>(new Shader(VertexShadersrc, FrgmentShadersrc));

		std::shared_ptr<VertexBuffer> Vbuff(VertexBuffer::Create(data, sizeof(data)));
		Vbuff->SpecifyLayout({
			{ ShaderDataType::Float3, "a_Position" }

			});

		std::shared_ptr<IndexBuffer> Ibuff(IndexBuffer::Create(indices, sizeof(indices)));


		m_VaoT = std::shared_ptr<VertexArray>(VertexArray::Create());
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

		m_shaderS = std::shared_ptr<Shader>(new Shader(VertexShadersrcS, FrgmentShadersrcS));

		std::shared_ptr<VertexBuffer> VbuffS(VertexBuffer::Create(dataS, sizeof(dataS)));
		VbuffS->SpecifyLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }

			});

		std::shared_ptr<IndexBuffer> IbuffS(IndexBuffer::Create(indicesS, sizeof(indicesS)));


		m_VaoS = std::shared_ptr<VertexArray>(VertexArray::Create());
		m_VaoS->AttachVertexBuffer(VbuffS);
		m_VaoS->AttachIndexBuffer(IbuffS);

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.pushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.pushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClosedEvent(WindowCloseEvent& event) {

		HK_CORE_TRACE("EVENT_OCCURED:{}", event.toString());

		m_Running = false;
		return true;
	}


}