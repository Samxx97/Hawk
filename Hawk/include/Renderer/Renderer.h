
#include "glm/glm.hpp"

namespace Hawk {

	class VertexArray;
	class Shader;
	class OrthographicCamera;

	class HAWK_API Renderer {

	public:

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform);

		struct SceneData
		{
			glm::mat4 ViewProjection;

		};

		static SceneData* m_Data;
	};


}