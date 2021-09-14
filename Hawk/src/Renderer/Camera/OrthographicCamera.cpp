#include "Renderer/Camera/OrthographicCamera.h"
#include "glm/ext.hpp"


namespace Hawk {

	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
		: m_Position(glm::vec3(0.0f, 0.0f, 0.0f)), m_RollAngle(0.0f)

	{
		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		Update();
	}

	void OrthographicCamera::Update()
	{
		m_Tranform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_RollAngle), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ViewProjection = m_Projection * glm::inverse(m_Tranform);
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		Update();
	}

	void OrthographicCamera::SetRotation(float angle)
	{
		m_RollAngle = angle;
		Update();
	}

}