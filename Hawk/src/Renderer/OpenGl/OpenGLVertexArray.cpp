#include "Renderer/Opengl/OpenGLVertexArray.h"
#include "Renderer/Buffer.h"
#include "glad/glad.h"

namespace Hawk {

	OpenGLVertexArray::OpenGLVertexArray() : m_AttributeIndex(0)
	{
		glGenVertexArrays(1, &m_vao);
		//glBindVertexArray(m_vao);


	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_vao);

	}

	void OpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AttachVertexBuffer(const Hawk::Ref<VertexBuffer>& Vbuffer)
	{
		HK_CORE_ASSERT(Vbuffer->GetLayout().GetAttributesCount(), "Buffer has no Layout!");

		glBindVertexArray(m_vao);

		Vbuffer->Bind(m_vao);

		const auto& layout = Vbuffer->GetLayout();
		for (const auto& attrib : layout)
		{

			glEnableVertexAttribArray(m_AttributeIndex);
			glVertexAttribPointer(m_AttributeIndex, ComponentCountOf(attrib.Type), GL_FLOAT, attrib.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (void*)attrib.Offset);
			m_AttributeIndex++;
		}


		m_VertexBuffers.push_back(Vbuffer);

		glBindVertexArray(0);

	}

	void OpenGLVertexArray::AttachIndexBuffer(const Hawk::Ref<IndexBuffer>& Ibuffer)
	{
		glBindVertexArray(m_vao);

		Ibuffer->Bind(m_vao);
		m_IndexBuffer = Ibuffer;

		glBindVertexArray(0);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_vao);
	}
}