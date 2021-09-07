#include "Renderer/Opengl/OpenGLVertexArray.h"
#include "Renderer/Buffer.h"
#include "glad/glad.h"

namespace Hawk {

	OpenGLVertexArray::OpenGLVertexArray() : m_AttributeIndex(0)
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_vao);

	}

	void OpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AttachVertexBuffer(const std::shared_ptr<VertexBuffer>& Vbuffer)
	{
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

	}

	void OpenGLVertexArray::AttachIndexBuffer(const std::shared_ptr<IndexBuffer>& Ibuffer)
	{
		glBindVertexArray(m_vao);

		Ibuffer->Bind(m_vao);
		m_IndexBuffer = Ibuffer;

	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_vao);
	}
}