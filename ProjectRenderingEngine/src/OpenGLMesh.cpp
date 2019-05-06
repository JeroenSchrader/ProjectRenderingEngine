#include "OpenGLMesh.h"
#include <iostream>
#include <string>

#define glCheckCall(glFunction) \
	glFunction; \
	glCheckError(#glFunction)

void glCheckError(std::string functionName)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::string message = "OpenGL function call ";
		if (functionName.compare("") != 0)
		{
			message += functionName;
			message += ' ';
		}
		message += "caused OpenGL error: ";

		switch (error)
		{
		case GL_INVALID_ENUM:
			message += "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			message += "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			message += "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			message += "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			message += "GL_OUT_OF_MEMORY";
			break;
		case GL_STACK_UNDERFLOW:
			message += "GL_STACK_UNDERFLOW";
			break;
		case GL_STACK_OVERFLOW:
			message += "GL_STACK_OVERFLOW";
			break;
		default:
			break;
		}

		std::cout << message << std::endl;
	}
}

OpenGLMesh::OpenGLMesh()
{
}

OpenGLMesh::~OpenGLMesh()
{
	//Delete vao, vbos, and ibo
	m_vbo->~VertexBuffer();
	m_ibo->~IndexBuffer();
	m_vao->~VertexArray();
}

void OpenGLMesh::CreateOpenGLData()
{
	VertexBuffer* vbo = new VertexBuffer(this->GetVertices().data(), this->GetVertices().size() * sizeof(float));
	m_vbo = vbo;

	VertexArray* vao = new VertexArray;
	m_vao = vao;

	m_vbo->Bind();
	const auto& elements = m_Layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		glCheckCall(glEnableVertexAttribArray(i));
		glCheckCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, m_Layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

	IndexBuffer* ibo = new IndexBuffer(this->GetIndices().data(), this->GetIndices().size());
	m_ibo = ibo;
}
