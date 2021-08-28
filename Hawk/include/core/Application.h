#pragma once

#include "hawk_exports.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

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


	protected:


	private:

		void Init();
		bool OnWindowClosedEvent(WindowCloseEvent&);
		bool OnWindowResizeEvent(WindowResizeEvent&);
		bool onMouseMoveEvent(MouseMovedEvent&);
		bool onMouseButtonPressed(MouseButtonPressedEvent&);
		bool onMouseButtonReleased(MouseButtonReleasedEvent&);

		EventDispatcher m_EventDispatcher;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		static Application* s_Instance;

	};

	//to be defined by Client
	Application* CreateApplication();


}