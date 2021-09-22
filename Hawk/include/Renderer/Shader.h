#include "glm/glm.hpp"

namespace Hawk {

	class HAWK_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		inline virtual const std::string& GetName() const = 0;
		inline virtual void SetName(const std::string& name) = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertexsrc, const std::string& fragmentsrc);
		static Ref<Shader> Create(const std::string& path);
	};

	class HAWK_API ShaderLibrary
	{
	public:
		ShaderLibrary() = default;
		~ShaderLibrary() = default;

		Ref<Shader> Load(const std::string& path);
		Ref<Shader> Load(const std::string& path, const std::string& shadername);

		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);

		Ref<Shader> Get(const std::string& name);


	private:

		bool Exists(const std::string& name) const;

		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	};

}