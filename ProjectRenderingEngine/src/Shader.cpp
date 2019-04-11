#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string & shaderSource)
	: m_Id(0)
{
	ShaderProgramSource source = ParseShader(shaderSource);
	m_Id = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

void Shader::Bind() const
{
	glUseProgram(m_Id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string & name)
{
	int location = glGetUniformLocation(m_Id, name.c_str());
	if (location == -1) {
		std::cout << "WARNING: Uniform location for uniform " << name << " not found" << std::endl;
	}
	return location;
}

void Shader::SetUniform3f(const std::string & name, float f1, float f2, float f3)
{
	glUniform3f(GetUniformLocation(name), f1, f2, f3);
}

void Shader::SetUniform4f(const std::string & name, float f1, float f2, float f3, float f4)
{	
	glUniform4f(GetUniformLocation(name), f1, f2, f3, f4);
}

void Shader::SetUniformMatrix4f(const std::string & name, glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

enum ShaderTypes {
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

Shader::ShaderProgramSource Shader::ParseShader(const std::string & filepath)
{
	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss[2];
	ShaderTypes type = ShaderTypes::NONE;
	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderTypes::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderTypes::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, std::string & source)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int succes;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR: Compiling of " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader failed" << std::endl;
		std::cout << infoLog << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

unsigned int Shader::CreateShader(std::string & vertexShaderSource, std::string & fragmentShaderSource)
{
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	int succes;
	glGetProgramiv(program, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		char infoLog[512];
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR: Linking of program failed" << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}
