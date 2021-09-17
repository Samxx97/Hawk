
#include "glm/glm.hpp"

namespace Hawk {

	class VertexArray;
	class Shader;
	class OrthographicCamera;

	class HAWK_API Renderer {

	public:

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Hawk::Ref<VertexArray>& vertexArray, const Hawk::Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		struct SceneData
		{
			glm::mat4 ViewProjection;

		};

		static SceneData* m_Data;
	};


}