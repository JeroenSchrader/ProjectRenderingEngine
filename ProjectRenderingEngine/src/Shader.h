#pragma once

#include <string>
#include "GLM/mat4x4.hpp"

class Shader {
private:
	struct ShaderProgramSource {
		std::string vertexSource;
		std::string fragmentSource;
	};

	unsigned int m_Id;	
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, std::string& source);
	unsigned int CreateShader(std::string& vertexShaderSource, std::string& fragmentShaderSource);

public:
	Shader(const std::string& shaderSource);
	~Shader();

	void Bind() const;
	void Unbind() const;

	int GetUniformLocation(const std::string& name);
	void SetUniform1f(const std::string& name, float f1);
	void SetUniform3f(const std::string& name, float f1, float f2, float f3);
	void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void SetUniformMatrix4f(const std::string& name, glm::mat4& matrix);
};