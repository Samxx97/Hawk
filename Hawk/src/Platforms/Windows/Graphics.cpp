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

	}

	void OpenGLContext::SwapBuffers() {

		glfwSwapBuffers(m_WindowHandle);

	}

}