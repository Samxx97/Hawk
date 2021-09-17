#include "Renderer/VertexArray.h"

namespace Hawk {

	class OpenGLVertexArray : public VertexArray {

	public:

		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() override;
		void UnBind() override;

		void AttachVertexBuffer(const Hawk::Ref<VertexBuffer>& Vbuffer) override;
		void AttachIndexBuffer(const Hawk::Ref<IndexBuffer>& Ibuffer) override;

		inline const Hawk::Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };

	private:

		uint32_t m_vao;
		std::vector<Hawk::Ref<VertexBuffer>> m_VertexBuffers;
		Hawk::Ref<IndexBuffer> m_IndexBuffer;
		size_t m_AttributeIndex;
	};

}