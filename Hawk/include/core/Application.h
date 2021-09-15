#pragma once

#include "Events/ApplicationEvent.h"

#include "Window.h"
#include "Layers/LayerStack.h"


namespace Hawk {

	class ImGuiLayer;

	class HAWK_API Application {

	public:

		Application();
		virtual ~Application() = default;

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; };
		inline static  Application& GetInstance() { return *s_Instance; }

	private:

		void Init();
		bool OnWindowClosedEvent(WindowCloseEvent&);

		EventDispatcher m_EventDispatcher;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		std::unique_ptr<Window> m_Window;
		TimeStep m_TimeStep;

		bool m_Running = true;
		static Application* s_Instance;

	};

	//to be defined by Client
	Application* CreateApplication();

}