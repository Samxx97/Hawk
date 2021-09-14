#include "glm/glm.hpp"

namespace Hawk {

	class RenderAPI;
	class VertexArray;

	class HAWK_API RenderCommand
	{
	public:

		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

	private:
		static RenderAPI* s_RenderAPI;
	};



}