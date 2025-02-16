#include "Entity.h"

#include "GLM/gtx/transform.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "OpenGLMesh.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

#include "LightingInformation.h"

Entity::Entity(std::string& name, OpenGLMesh* mesh, Material* material, Texture* textureMap, Texture* normalMap, glm::vec3 position, glm::vec3 rotations, glm::vec3 scale)
	: m_Name(name), m_Mesh(mesh), m_Material(material), m_TextureMap(textureMap), m_NormalMap(normalMap), m_Position(position), m_Rotation(rotations), m_Scale(scale)
{
}

Entity::~Entity()
{
	(*m_Mesh).~OpenGLMesh();
	(*m_Material).~Material();
}

glm::mat4 Entity::GetTransformationMatrix()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 scaleMatrix = glm::scale(m_Scale);
	glm::mat4 rotationX = glm::rotate(glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotationMatrix = rotationX * rotationY * rotationZ;
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	return transformationMatrix;	
}

const void Entity::Bind() {
	m_Mesh->GetVao()->Bind();
	m_Material->BindShader();
	m_NormalMap->Bind();
	m_TextureMap->Bind();
	if (GetName().find("Light") == std::string::npos) {
		m_Material->GetShader()->SetUniform1i("u_TextureMap", (int)TextureTypes::TextureMap);
		m_Material->GetShader()->SetUniform1i("u_NormalMap", (int)TextureTypes::NormalMap);
	}
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

const void Entity::SetLightingInformation(LightingInformation& information)
{
	m_Material->GetShader()->SetUniform1f("u_ambientLightStrength", information.AmbientStrength);
	m_Material->GetShader()->SetUniform3f("u_ambientLightColor", information.AmbientColor.x, information.AmbientColor.y, information.AmbientColor.z);
	m_Material->GetShader()->SetUniform3f("u_diffuseLightColor", information.DiffuseColor.x, information.DiffuseColor.y, information.DiffuseColor.z);
	m_Material->GetShader()->SetUniform1f("u_diffuseLightStrength", information.DiffuseStrength);
	m_Material->GetShader()->SetUniform3f("u_lightPosition", information.Position.x, information.Position.y, information.Position.z);
	m_Material->GetShader()->SetUniform3f("u_specularLightColor", information.SpecularColor.x, information.SpecularColor.y, information.SpecularColor.z);
	m_Material->GetShader()->SetUniform1f("u_specularLightStrength", information.SpecularStrength);
	m_Material->GetShader()->SetUniform3f("u_cameraPosition", information.CameraPosition.x, information.CameraPosition.y, information.CameraPosition.z);

	Material* material = GetMaterial();
	m_Material->GetShader()->SetUniform3f("u_Material.ambient", material->GetAmbient().x, material->GetAmbient().y, material->GetAmbient().z);
	m_Material->GetShader()->SetUniform3f("u_Material.diffuse", material->GetDiffuse().x, material->GetDiffuse().y, material->GetDiffuse().z);
	m_Material->GetShader()->SetUniform3f("u_Material.specular", material->GetSpecular().x, material->GetSpecular().y, material->GetSpecular().z);
	m_Material->GetShader()->SetUniform1f("u_Material.shininess", material->GetShininess());
}


