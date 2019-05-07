#include "Entity.h"

#include "GLM/gtx/transform.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

Entity::Entity(Mesh* mesh, Material* material, glm::vec3 position, glm::vec3 rotations, glm::vec3 scale)
	: m_Mesh(mesh), m_Material(material), m_Position(position), m_RotationXInDegrees(rotations.x), m_RotationYInDegrees(rotations.y), m_RotationZInDegrees(rotations.z), m_Scale(scale)
{
}

Entity::~Entity()
{
	(*m_Mesh).~Mesh();
	(*m_Material).~Material();
}

glm::mat4 Entity::GetTransformationMatrix()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 scaleMatrix = glm::scale(m_Scale);
	glm::mat4 rotationX = glm::rotate(glm::radians(m_RotationXInDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(glm::radians(m_RotationYInDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(glm::radians(m_RotationZInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotationMatrix = rotationX * rotationY * rotationZ;
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	return transformationMatrix;	
}

const void Entity::BindMaterial()
{
	m_Material->BindShader();
}

const void Entity::SetProjectionMatrix(glm::mat4 projectionMatrix)
{
	m_Material->GetShader()->SetUniformMatrix4f("u_projectionMatrix", projectionMatrix);
}

const void Entity::SetViewMatrix(glm::mat4 viewMatrix)
{
	m_Material->GetShader()->SetUniformMatrix4f("u_viewMatrix", viewMatrix);
}

const void Entity::SetTransformationMatrix(glm::mat4 transformationMatrix)
{
	m_Material->GetShader()->SetUniformMatrix4f("u_transformationMatrix", transformationMatrix);
}
