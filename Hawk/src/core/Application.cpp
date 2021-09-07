#include "Core/Application.h"
#include "Core/Core.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include "glad/glad.h"

#include "ImGui/ImGuiLayer.h"

namespace Hawk {

	Application* Application::s_Instance = nullptr;


	Application::Application()
	{
		Init();
	}

	void Application::Run()
	{

		m_LayerStack.SetupEvents(m_EventDispatcher);

		while (m_Running) {


			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_Vao->Bind();
			glDrawElements(GL_TRIANGLES, m_Vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);


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
		PushLayer(m_ImGuiLayer);


		//Register Application EventHandlers
		m_EventDispatcher.Subscribe<WindowCloseEvent>(BIND_EVENT_FN_DEFAULT(Application::OnWindowClosedEvent));


		float data[] = {
	   -0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		 0.0f,0.5f,0.0f
		};

		unsigned int indices[3] = { 0, 1, 2 };

		std::shared_ptr<VertexBuffer> Vbuff(VertexBuffer::Create(data, sizeof(data)));
		Vbuff->SpecifyLayout({
			{ ShaderDataType::Float3, "Position" }

			});

		std::shared_ptr<IndexBuffer> Ibuff(IndexBuffer::Create(indices, sizeof(indices)));


		m_Vao = VertexArray::Create();
		m_Vao->AttachVertexBuffer(Vbuff);
		m_Vao->AttachIndexBuffer(Ibuff);

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