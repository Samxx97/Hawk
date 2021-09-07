#include "Renderer/Opengl/OpenGLBuffer.h"
#include "glad/glad.h"

namespace Hawk {

	///////////////////////////////////////////////////////////////////////
	/////////////////////////Vertex Buffer/////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size)
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		//unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void OpenGLVertexBuffer::Bind(uint32_t vao)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	}

	void OpenGLVertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void OpenGLVertexBuffer::SpecifyLayout(const BufferLayout& layout)
	{
		m_layout = layout;

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_vbo);
	}

	///////////////////////////////////////////////////////////////////////
	/////////////////////////Index Buffer//////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t size) : count(size / sizeof(uint32_t))
	{
		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		//unbind
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void OpenGLIndexBuffer::Bind(uint32_t vao)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);


	}

	void OpenGLIndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_ibo);
	}


}