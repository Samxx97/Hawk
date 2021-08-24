
#include "Core/Application.h"
#include "Core/Core.h"



#include "glad/glad.h"

#include  "ImGui/ImGuiLayer.h"
#include "GLFW/glfw3.h"

namespace Hawk {

	Application* Application::s_Instance = nullptr;


	Application::Application() {
		Init();
	}

	void Application::Run() {

		m_LayerStack.setupEvents(m_EventDispatcher);

		while (m_Running) {

			glClearColor(01.0, 0.2, 0.6, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();





		}
	}


	void Application::Init() {

		HK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		Log::init();
		HK_CORE_TRACE("Initializing Application");

		m_Window = std::unique_ptr<Window>(Window::Create(m_EventDispatcher));


		//Register Application EventHandlers
		m_EventDispatcher.Subscribe<WindowCloseEvent>(BIND_EVENT_FN_DEFAULT(Application::OnWindowClosedEvent));
		m_EventDispatcher.Subscribe<WindowResizeEvent>(BIND_EVENT_FN_DEFAULT(Application::OnWindowResizeEvent));
		m_EventDispatcher.Subscribe<MouseMovedEvent>(BIND_EVENT_FN_DEFAULT(Application::onMouseMoveEvent));
		m_EventDispatcher.Subscribe<MouseButtonPressedEvent>(BIND_EVENT_FN_DEFAULT(Application::onMouseButtonPressed));
		m_EventDispatcher.Subscribe<MouseButtonReleasedEvent>(BIND_EVENT_FN_DEFAULT(Application::onMouseButtonReleased));


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

	bool Application::OnWindowResizeEvent(WindowResizeEvent& event) {

		HK_CORE_TRACE("EVENT_OCCURED:{}", event.toString());

		return true;

	}

	bool Application::onMouseMoveEvent(MouseMovedEvent& event) {

		HK_CORE_TRACE("EVENT_OCCURED:{}", event.toString());

		return true;

	}
	bool Application::onMouseButtonPressed(MouseButtonPressedEvent& event) {

		HK_CORE_TRACE("EVENT_OCCURED:{}", event.toString());




		return true;

	}
	bool Application::onMouseButtonReleased(MouseButtonReleasedEvent& event) {

		HK_CORE_TRACE("EVENT_OCCURED:{}", event.toString());

		return true;

	}

}