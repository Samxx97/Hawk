#include "Renderer/Opengl/OpenGLShader.h"
#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"
#include "Core/Core.h"
#include <fstream>

namespace Hawk {

	GLenum ShaderTypeToGlenum(const std::string& type)
	{
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		else if (type == "vertex")
			return GL_VERTEX_SHADER;

		else
		{
			HK_CORE_ASSERT(false, "shader type keyword not allowed!");
			return 0;
		}
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderMap{
			{GL_VERTEX_SHADER, vertexSrc},
			{GL_FRAGMENT_SHADER, fragmentSrc} };

		Compile(shaderMap);

	}

	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::ifstream file(path);

		HK_CORE_ASSERT(file, "File didnt Open wrong path");

		file.seekg(0, std::ios::end);
		size_t size = file.tellg();

		std::string buffer(size, ' ');
		file.seekg(0);
		file.read(&buffer[0], size);
		file.close();

		//TODO change it to become the last name in path
		m_Name = "path";

		std::unordered_map<GLenum, std::string>shaderMap = Preprocess(buffer);
		Compile(shaderMap);

	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& file)
	{
		std::unordered_map<GLenum, std::string> shaderMap;
		std::string buff(file);

		std::string prefix("#type");
		size_t prefix_length = prefix.size() + 1;
		size_t KeywordLength = 0;


		size_t pos = buff.find(prefix);

		while (pos != std::string::npos)
		{
			size_t KeywordEndPos = buff.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz", pos + prefix_length);
			KeywordLength = KeywordEndPos - (pos + prefix_length);

			GLenum shadertype = ShaderTypeToGlenum(buff.substr(pos + prefix_length, KeywordLength));

			size_t shadersrcBeg = buff.find_first_not_of("/n/r/t", KeywordEndPos);
			size_t shadersrcEnd = buff.find(prefix, pos + prefix_length);
			std::string shaderSrc = buff.substr(shadersrcBeg, shadersrcEnd == std::string::npos ? std::string::npos : shadersrcEnd - shadersrcBeg);

			shaderMap.insert({ shadertype, shaderSrc });

			buff = buff.substr(pos + prefix_length + KeywordLength);
			pos = buff.find(prefix);

		}

		return shaderMap;
	}


	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& shadermap)
	{
		GLuint program = glCreateProgram();

		std::array<GLuint, 5> shadersIDS;
		uint32_t idCount = 0;

		for (auto const& [shadertype, shadersrc] : shadermap)
		{

			GLuint shader = glCreateShader(shadertype);

			const GLchar* source = shadersrc.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				HK_CORE_ERROR("{0}", infoLog.data());
				HK_CORE_ASSERT(false, " shader compilation failure!");
				return;
			}

			glAttachShader(program, shader);
			shadersIDS[idCount++] = shader;

		}


		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto& id : shadersIDS) {

				glDeleteShader(id);

			}


			HK_CORE_ERROR("{0}", infoLog.data());
			HK_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		//detach the shaders because they arent needed anymore
		for (auto& id : shadersIDS)

			glDetachShader(program, id);


		m_RendererID = program;

	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}