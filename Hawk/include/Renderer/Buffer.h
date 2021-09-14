#include "Core/Core.h"

namespace Hawk {

	enum class ShaderDataType
	{
		Float4,
		Float3,
		Float2,
		Float,
		Int4,
		Int3,
		Int2,
		Int,
		Mat4,
		Mat3,
		Mat2,
		Bool
	};

	inline size_t SizeOfType(ShaderDataType datatype) {

		switch (datatype)
		{

		case ShaderDataType::Float4: return sizeof(float) * 4;

		case ShaderDataType::Float3: return sizeof(float) * 3;

		case ShaderDataType::Float2: return sizeof(float) * 2;

		case ShaderDataType::Float: return sizeof(float);

		case ShaderDataType::Mat4: return sizeof(float) * 4 * 4;

		case ShaderDataType::Mat3: return sizeof(float) * 4 * 3;

		case ShaderDataType::Mat2: return sizeof(float) * 4 * 2;

		case ShaderDataType::Int4: return sizeof(int) * 4;

		case ShaderDataType::Int3: return sizeof(int) * 3;

		case ShaderDataType::Int2: return sizeof(int) * 2;

		case ShaderDataType::Int: return sizeof(int);

		case ShaderDataType::Bool: return sizeof(byte);

		}

		HK_CORE_ASSERT(false, "Unknown ShaderData Type!");
		return 0;
	}

	inline size_t ComponentCountOf(ShaderDataType datatype) {

		switch (datatype)
		{
		case ShaderDataType::Float4: return 4;

		case ShaderDataType::Float3: return 3;

		case ShaderDataType::Float2: return 2;

		case ShaderDataType::Float: return 1;

		case ShaderDataType::Int4: return 4;

		case ShaderDataType::Int3: return 3;

		case ShaderDataType::Int2: return 2;

		case ShaderDataType::Int: return 1;

		}
		HK_CORE_ASSERT(false, "Unknown ShaderData Type!");
		return 0;

	}
	struct BufferAttrib {

		BufferAttrib() {};

		BufferAttrib(ShaderDataType type, const std::string& name, bool normalized = false) :
			Type(type), Name(name), Offset(0), Size(SizeOfType(type)), Normalized(normalized)
		{
		}

		ShaderDataType Type;
		std::string Name;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;
	};

	class BufferLayout {

		using Iterator = std::vector<BufferAttrib>::iterator;
		using const_Iterator = std::vector<BufferAttrib>::const_iterator;

	public:

		BufferLayout() {};

		BufferLayout(const std::initializer_list<BufferAttrib>& attributes) : m_Stride(0), m_Attributes(attributes)
		{

			uint32_t offset = 0;
			for (auto& attrib : m_Attributes) {
				attrib.Offset = offset;
				offset += attrib.Size;
				m_Stride += attrib.Size;

			}

		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline size_t GetAttributesCount() const { return m_Attributes.size(); }

		/*Iterator begin() { return m_Attributes.begin(); }
		Iterator end() { return  m_Attributes.end(); }*/

		//only permit to read from elements not modify
		const_Iterator begin() const { return m_Attributes.begin(); }
		const_Iterator end() const { return  m_Attributes.end(); }


	private:
		std::vector<BufferAttrib> m_Attributes;
		uint32_t m_Stride;

	};

	class VertexBuffer {

	public:
		virtual ~VertexBuffer() {};

		virtual void Bind(uint32_t vao) = 0;
		virtual void UnBind() = 0;

		virtual void SpecifyLayout(const BufferLayout& layout) = 0;

		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* data, uint32_t size);
	};

	class IndexBuffer {

	public:
		virtual ~IndexBuffer() {};

		virtual void Bind(uint32_t vao) = 0;
		virtual void UnBind() = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* data, uint32_t size);

	};


}