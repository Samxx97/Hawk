#include "Renderer/VertexArray.h"

namespace Hawk {

	class OpenGLVertexArray : public VertexArray {

	public:

		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() override;
		void UnBind() override;

		void AttachVertexBuffer(const std::shared_ptr<VertexBuffer>& Vbuffer) override;
		void AttachIndexBuffer(const std::shared_ptr<IndexBuffer>& Ibuffer) override;

		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };

	private:

		uint32_t m_vao;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		size_t m_AttributeIndex;
	};

}