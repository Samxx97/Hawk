#include "Renderer/RenderAPI.h"

namespace Hawk {

	class OpenGLRenderAPI : public RenderAPI {

	public:

		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};


}