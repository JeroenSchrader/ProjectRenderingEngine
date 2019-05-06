#pragma once

#include "Mesh.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class OpenGLMesh : public Mesh {
private:
	VertexArray* m_vao;
	VertexBuffer* m_vbo;
	IndexBuffer* m_ibo;
	VertexBufferLayout m_Layout;

public:
	OpenGLMesh();
	~OpenGLMesh();

	inline VertexArray* GetVao() { return m_vao; }
	inline VertexBuffer* GetVbo() { return m_vbo; }
	inline IndexBuffer* GetIbo() { return m_ibo; }
	inline VertexBufferLayout& GetLayout() { return m_Layout; }

	void CreateOpenGLData();
};