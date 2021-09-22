#include "Renderer/Shader.h"
#include "glm/glm.hpp"

typedef unsigned int GLenum;

namespace Hawk {

	class HAWK_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& path);

		virtual ~OpenGLShader();

		std::unordered_map <GLenum, std::string> Preprocess(const std::string& file);
		void Compile(std::unordered_map<GLenum, std::string>& shadermap);

		void Bind() const override;
		void Unbind() const override;
		inline const std::string& GetName() const override { return m_Name; };
		inline void SetName(const std::string& name)  override { m_Name = name; }


		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}