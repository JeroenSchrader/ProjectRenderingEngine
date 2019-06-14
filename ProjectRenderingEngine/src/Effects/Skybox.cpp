#include "Skybox.h"
#include "Cubemap.h"
#include "Shader.h"
#include "OpenGLMesh.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

Skybox::Skybox(Cubemap* cubemap, Shader* shader, OpenGLMesh* mesh)
	: m_CubeMap(cubemap), m_Shader(shader), m_Mesh(mesh)
{
}

void Skybox::Bind(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	glDepthFunc(GL_LEQUAL);
	m_Shader->Bind();
	m_Shader->SetUniformMatrix4f("u_projectionMatrix", projectionMatrix);
	m_Shader->SetUniformMatrix4f("u_viewMatrix", viewMatrix);
	m_Mesh->GetVao()->Bind();
	m_CubeMap->Bind();
}
