#include "Core/Application.h"
#include "Core/Core.h"

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

			m_TimeStep.Tick();

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(m_TimeStep);
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