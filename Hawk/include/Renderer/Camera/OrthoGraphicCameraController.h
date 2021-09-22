#include "Renderer/Camera/OrthographicCamera.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace Hawk {

	class TimeStep;

	class HAWK_API OrthoGraphicCameraController
	{
	public:

		OrthoGraphicCameraController(float aspectratio, const glm::vec3& position = glm::vec3(0.0f), float rotation = 0) : m_AspectRatio(aspectratio), m_Position(position),
			m_Rotation(rotation), m_ZoomLevel(1.0f),
			m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, 1.0f * m_ZoomLevel, -1.0f * m_ZoomLevel) {};

		void OnUpdate(TimeStep ts);
		bool OnMouseScroll(MouseScrolledEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		inline const OrthographicCamera& GetCamera() const { return m_Camera; };

	private:
		float m_AspectRatio;
		float m_ZoomLevel;

		OrthographicCamera m_Camera;

		glm::vec3 m_Position;
		float m_Rotation;

		//  units/Secs
		float m_MovementSpeed = 5.0f;
		float m_RotationSpeed = 80.0f;

	};


}