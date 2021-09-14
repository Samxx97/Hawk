#include "glm/glm.hpp"

namespace Hawk {

	class HAWK_API OrthographicCamera {

	public:
		OrthographicCamera(float left, float right, float top, float bottom);

		void Update();

		void SetPosition(const glm::vec3& position);
		inline const glm::vec3& GetPosition() const { return m_Position; }

		void SetRotation(float angle);
		inline float GetRotation() const { return m_RollAngle; }

		inline const glm::mat4& GetViewProjection()const { return m_ViewProjection; }

	private:
		glm::mat4 m_ViewProjection;
		glm::mat4 m_Tranform;
		glm::mat4 m_Projection;

		glm::vec3 m_Position;
		float m_RollAngle = 0;
	};

}