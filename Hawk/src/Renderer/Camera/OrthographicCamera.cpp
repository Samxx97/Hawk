#include "Renderer/Camera/OrthographicCamera.h"
#include "glm/ext.hpp"


namespace Hawk {

	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)

	{
		m_Projection = glm::ortho(left, right, bottom, top, -2.0f, 2.0f);

	}

	void OrthographicCamera::Update(const glm::vec3& position, float rotation)
	{
		m_Tranform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		RecalculateViewProjection();

	}
	void OrthographicCamera::Update(float left, float right, float top, float bottom)
	{
		m_Projection = glm::ortho(left, right, bottom, top, -2.0f, 2.0f);
		RecalculateViewProjection();

	}

	void OrthographicCamera::RecalculateViewProjection()
	{
		m_ViewProjection = m_Projection * glm::inverse(m_Tranform);


	}

}