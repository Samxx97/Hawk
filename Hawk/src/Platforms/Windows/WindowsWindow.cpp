#include "Platforms/Windows/WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "glad/glad.h"

#include "GLFW/glfw3.h"

namespace Hawk {


	template<class T>
	bool WindowsWindow<T>::s_Glfw_initiliazed = false;


	template<class T>
	WindowsWindow<T>::WindowsWindow(T& eventHandler, const WindowProps& props) : m_Data(eventHandler) {

		Init(props);

	}


	template<class T>
	WindowsWindow<T>::~WindowsWindow() {

		glfwDestroyWindow(m_Window);
	}

	template<class T>
	void WindowsWindow<T>::Init(const WindowProps& props) {

		glfwSetErrorCallback([](int error, const char* description) {HK_CORE_ERROR("GLFW_Error ({0}): {1}", error, description); });

		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		HK_CORE_INFO("Creating Window {0} ({1},{2})", props.Title, props.Width, props.Height);

		if (!s_Glfw_initiliazed) {

			int success = glfwInit();
			HK_CORE_ASSERT(success, "Could not initiliaze GLFW!");

			s_Glfw_initiliazed = true;

		}



		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, props.Title.c_str(), nullptr, nullptr);

		HK_CORE_ASSERT(m_Window, "Could not initiliaze GLFW!");



		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HK_CORE_ASSERT(status, "Could not initiliaze Glad!");


		SetVSync(true);

		glfwSetWindowUserPointer(m_Window, &m_Data);

		//set up event callbacks

		//Window Events
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;

			data.eventHandler.Post<WindowCloseEvent>(event);

		});


		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.Width = width;
			data.Height = height;


			WindowResizeEvent event(width, height);
			data.eventHandler.Post<WindowResizeEvent>(event);
		});


		//Key Events
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action) {

			case(GLFW_PRESS):
			{
				KeyPressedEvent event(key, 0);
				data.eventHandler.Post<KeyPressedEvent>(event);
				break;
			}
			case(GLFW_RELEASE):
			{
				KeyReleasedEvent event(key);
				data.eventHandler.Post<KeyReleasedEvent>(event);
				break;
			}
			case(GLFW_REPEAT):
			{
				KeyPressedEvent event(key, 1);
				data.eventHandler.Post<KeyPressedEvent>(event);
				break;
			}

			}

		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int characterKey) {

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			KeyTypedEvent event(characterKey);

			data.eventHandler.Post<KeyTypedEvent>(event);

		});

		//Mouse Events

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(xpos, ypos);
			data.eventHandler.Post<MouseMovedEvent>(event);

		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(xoffset, yoffset);
			data.eventHandler.Post<MouseScrolledEvent>(event);

		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action) {

			case(GLFW_PRESS):
			{
				MouseButtonPressedEvent event(button);
				data.eventHandler.Post<MouseButtonPressedEvent>(event);
				break;

			}
			case(GLFW_RELEASE):
			{
				MouseButtonReleasedEvent event(button);
				data.eventHandler.Post<MouseButtonReleasedEvent>(event);
				break;

			}

			}


		});


	}

	template <class T>
	void WindowsWindow<T>::OnUpdate() {

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	template <class T>
	void WindowsWindow<T>::SetVSync(bool enabled) {

		enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);
		m_Data.IsVSync = enabled;
	}


	//instantiating the templates with EventDispatcher  to provide member function implementations to silence linker errors


	template<>
	static Window* Window::Create(EventDispatcher& eventHandler, const WindowProps& props) {
		return new WindowsWindow<EventDispatcher>(eventHandler, props);
	}

	template class WindowsWindow<EventDispatcher>;


}