#pragma once

class Cubemap;
class Shader;
class OpenGLMesh;

#include <vector>
#include "GLM/mat4x4.hpp"

class Skybox {
public:
	Skybox(Cubemap* cubemap, Shader* shader, OpenGLMesh* mesh);
	~Skybox() = default;

	void Bind(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

private:
	Cubemap* m_CubeMap;
	Shader* m_Shader;
	OpenGLMesh* m_Mesh;
};

static std::vector<float> skyboxVertices = {

	-1.0f,  1.0f, -1.0f,	//0	
	-1.0f, -1.0f, -1.0f,	//1
	 1.0f, -1.0f, -1.0f,	//2
	 1.0f,  1.0f, -1.0f,	//3

	-1.0f, -1.0f,  1.0f,	//4
	-1.0f,  1.0f,  1.0f,	//5
	 1.0f, -1.0f,  1.0f,	//6
	 1.0f,  1.0f,  1.0f		//7
};

static std::vector<unsigned int> skyboxIndices = {
	0, 1, 2,
	2, 3, 0,

	4, 1, 0,
	0, 5, 4,
	
	2, 6, 7,
	7, 3, 2,
	
	4, 5, 7,
	7, 6, 4,

	0, 3, 7,
	7, 5, 0,

	1, 4, 2,
	2, 4, 6
};