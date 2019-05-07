#include "Material.h"
#include "Shader.h"

Material::Material(const std::string& shaderPath)
{
	m_Shader = new Shader(shaderPath);
}

const void Material::BindShader() {
	m_Shader->Bind();
}
