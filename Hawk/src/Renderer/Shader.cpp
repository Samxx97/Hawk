#include "Renderer/RenderAPI.h"
#include "Renderer/Opengl/OpenGLShader.h"
#include "Core/Core.h"

namespace Hawk {

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexsrc, const std::string& fragmentsrc)
	{
		switch (RenderAPI::GraphicsAPI)
		{
		case RenderAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexsrc, fragmentsrc);

		case RenderAPI::API::None: HK_CORE_ASSERT(false, "no behavior is implemented for RenderAPI:None yet"); return nullptr;

		}

		HK_CORE_ASSERT(false, "No Rendering API is Selected!");
		return nullptr;

	}

	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (RenderAPI::GraphicsAPI)
		{
		case RenderAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);

		case RenderAPI::API::None: HK_CORE_ASSERT(false, "no behavior is implemented for RenderAPI:None yet"); return nullptr;

		}

		HK_CORE_ASSERT(false, "No Rendering API is Selected!");
		return nullptr;

	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();

	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		HK_CORE_ASSERT(!Exists(shader->GetName()), "a shader Already Exists with this name");
		m_Shaders[shader->GetName()] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HK_CORE_ASSERT(!Exists(name), "a shader Already Exists with this name");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& path, const std::string& shadername)
	{
		auto shader = Shader::Create(path);
		shader->SetName(shadername);
		Add(shadername, shader);
		return shader;


	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		HK_CORE_ASSERT(Exists(name), "thtis shader doesnt exist");
		return m_Shaders[name];
	}

}