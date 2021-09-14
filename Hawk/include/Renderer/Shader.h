#include "glm/glm.hpp"

namespace Hawk {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();

		void UploadeUniform(const glm::mat4& mat, const std::string& name);

	private:
		uint32_t m_RenderID;
	};

}