#include "Renderer/Camera/OrthoGraphicCameraController.h"
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Core/TimeStep.h"

namespace Hawk {

	void OrthoGraphicCameraController::OnUpdate(TimeStep ts)
	{
		if (Hawk::Input::IsKeyPressed(HK_KEY_A))
			m_Position.x -= m_MovementSpeed * ts;

		else if (Hawk::Input::IsKeyPressed(HK_KEY_D))
			m_Position.x += m_MovementSpeed * ts;

		if (Hawk::Input::IsKeyPressed(HK_KEY_S))
			m_Position.y -= m_MovementSpeed * ts;

		else if (Hawk::Input::IsKeyPressed(HK_KEY_W))
			m_Position.y += m_MovementSpeed * ts;

		if (Hawk::Input::IsKeyPressed(HK_KEY_M))
			m_Rotation -= m_RotationSpeed * ts;

		else if (Hawk::Input::IsKeyPressed(HK_KEY_N))
			m_Rotation += m_RotationSpeed * ts;

		m_Camera.Update(m_Position, m_Rotation);
		HK_CORE_INFO("rotation angle:{}", m_Rotation);

	}

	bool OrthoGraphicCameraController::OnMouseScroll(MouseScrolledEvent& event)
	{

		m_ZoomLevel -= event.GetYoffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.Update(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);
		return false;
	}

	bool OrthoGraphicCameraController::OnWindowResize(WindowResizeEvent& event)
	{
		if (event.GetHeight() == 0)
			return false;

		m_AspectRatio = event.GetWidth() / event.GetHeight();
		m_Camera.Update(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);

		return false;
	}

}