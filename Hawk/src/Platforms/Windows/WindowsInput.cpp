#pragma once

#include "Platforms/Windows/WindowsInput.h"
#include "GLFW/glfw3.h"


namespace Hawk {

	Input* Input::s_InputInstance = nullptr;

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		int state = glfwGetKey(m_window, keycode);

		return state == GLFW_PRESS;

	}

	bool WindowsInput::IsMouseKeyPressedImpl(int button)
	{
		int state = glfwGetMouseButton(m_window, button);

		return state == GLFW_PRESS;

	}


}