#pragma once

#include "Input/Input.h"

struct GLFWwindow;

namespace Hawk {

	class HAWK_API WindowsInput : public Input {

	public:

		WindowsInput(GLFWwindow* window) : m_window(window) {};

		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseKeyPressedImpl(int button) override;


	private:
		GLFWwindow* m_window;

	};


}