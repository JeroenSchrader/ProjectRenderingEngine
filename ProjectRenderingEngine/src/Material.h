#pragma once

#include <string>
class Shader;

class Material {
private:
	Shader* m_Shader;
public:
	Material(const std::string& shaderPath);
	~Material() = default;

	const void BindShader();

	inline Shader* GetShader() const { return m_Shader; }
};