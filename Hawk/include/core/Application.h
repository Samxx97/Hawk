#pragma once

#include "Events/ApplicationEvent.h"

#include "Window.h"
#include "Layers/LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/Camera/OrthographicCamera.h"

namespace Hawk {

	class ImGuiLayer;
	class VertexArray;

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

		std::shared_ptr<VertexArray> m_VaoT;
		std::shared_ptr<Shader> m_shaderT;

		std::shared_ptr<VertexArray> m_VaoS;
		std::shared_ptr<Shader> m_shaderS;

		EventDispatcher m_EventDispatcher;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		std::unique_ptr<Window> m_Window;

		OrthographicCamera m_Camera;

		bool m_Running = true;
		static Application* s_Instance;

	};

	//to be defined by Client
	Application* CreateApplication();

}