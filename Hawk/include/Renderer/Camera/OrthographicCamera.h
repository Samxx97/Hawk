#include "glm/glm.hpp"

namespace Hawk {

	class HAWK_API OrthographicCamera {

	public:
		OrthographicCamera(float left, float right, float top, float bottom);

		void Update(const glm::vec3& position, float rotation);
		void Update(float left, float right, float top, float bottom);


		inline const glm::mat4& GetViewProjection()const { return m_ViewProjection; }

	private:

		void RecalculateViewProjection();

		glm::mat4 m_ViewProjection;
		glm::mat4 m_Tranform;
		glm::mat4 m_Projection;

	};

}