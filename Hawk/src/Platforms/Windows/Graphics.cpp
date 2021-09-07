#include "Platforms/Windows/Graphics.h"
#include "Core/Core.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hawk {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		HK_CORE_ASSERT(windowHandle, "Window Handle is Null!");

	}

	void OpenGLContext::Init() {

		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HK_CORE_ASSERT(status, "Could not initiliaze Glad!");


		HK_CORE_INFO("OpenGL Info:");
		HK_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HK_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HK_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {

		glfwSwapBuffers(m_WindowHandle);

	}

}