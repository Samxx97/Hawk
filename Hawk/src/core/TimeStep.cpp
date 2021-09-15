#include "Core/TimeStep.h"
#include "GLFW/glfw3.h"

namespace Hawk {

	void TimeStep::Tick()
	{
		float currentFrame = glfwGetTime();
		m_Elapsed = currentFrame - m_LastFrame;
		m_LastFrame = currentFrame;

	}

	void TimeStep::Reset()
	{
		m_LastFrame = 0;
		m_Elapsed = 0;
	}
}