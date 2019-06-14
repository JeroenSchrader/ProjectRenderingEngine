#include "Material.h"
#include "Shader.h"

Material::Material(const std::string& shaderPath, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
	: m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess)
{
	m_Shader = new Shader(shaderPath);
}

Material::Material(const std::string& shaderPath, glm::vec3 color, float shininess)
	: m_Ambient(color), m_Diffuse(color), m_Specular(color), m_Shininess(shininess)
{
	m_Shader = new Shader(shaderPath);
}

const void Material::BindShader() {
	m_Shader->Bind();
}
