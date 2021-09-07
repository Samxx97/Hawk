#include "Renderer/Buffer.h" 

namespace Hawk {

	class OpenGLVertexBuffer : public VertexBuffer {

	public:

		OpenGLVertexBuffer(float* data, uint32_t size);
		~OpenGLVertexBuffer();

		void Bind(uint32_t vao) override;
		void UnBind() override;

		void SpecifyLayout(const BufferLayout& layout) override;

		inline const BufferLayout& GetLayout() const override { return m_layout; };

	private:

		uint32_t m_vbo;
		BufferLayout m_layout;
	};


	class OpenGLIndexBuffer : public IndexBuffer {

	public:

		OpenGLIndexBuffer(uint32_t* data, uint32_t size);
		~OpenGLIndexBuffer();

		void Bind(uint32_t vao) override;
		void UnBind() override;

		inline uint32_t GetCount() const override { return count; };

	private:
		uint32_t m_ibo;
		uint32_t count;
	};
}