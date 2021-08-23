#pragma once

#include "hawk_exports.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace Hawk {


	class HAWK_API Application {

	public:

		Application();
		virtual ~Application() = default;

		void Run();
		inline static  Application& GetInstance() { return *s_Instance; }


	private:

		void Init();
		bool OnWindowClosedEvent(WindowCloseEvent&);
		bool OnWindowResizeEvent(WindowResizeEvent&);
		bool onMouseMoveEvent(MouseMovedEvent&);
		bool onMouseButtonPressed(MouseButtonPressedEvent&);
		bool onMouseButtonReleased(MouseButtonReleasedEvent&);

		EventDispatcher m_EventDispatcher;

		bool m_Running = true;

		static Application* s_Instance;

	};

	//to be defined by Client
	Application* CreateApplication();


}