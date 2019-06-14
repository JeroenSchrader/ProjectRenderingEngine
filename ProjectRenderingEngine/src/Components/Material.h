#pragma once

#include <string>
#include "GLM/vec3.hpp"
class Shader;

class Material {
private:
	Shader* m_Shader;
	glm::vec3 m_Ambient;
	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;
	float m_Shininess;

public:
	Material(const std::string& shaderPath, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	Material(const std::string& shaderPath, glm::vec3 color, float shininess);
	~Material() = default;

	const void BindShader();

	inline Shader* GetShader() const { return m_Shader; }
	inline glm::vec3& GetAmbient() { return m_Ambient; }
	inline glm::vec3& GetDiffuse() { return m_Diffuse; }
	inline glm::vec3& GetSpecular() { return m_Specular; }
	inline float& GetShininess() { return m_Shininess; }

};