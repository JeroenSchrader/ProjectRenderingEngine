#include "ResourceManager.h"
#include "OpenGLMesh.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Entity.h"

//Basic 3D Cube vertices
std::vector<float> vertices{
	//Positions				//Colors
	-0.8f, -0.8f, 0.8f,		0.0f, 1.0f, 0.0f,	//front lower left	- index 0
	-0.8f,  0.8f, 0.8f,		1.0f, 0.0f, 0.0f,	//front upper left	- index 1
	 0.8f,  0.8f, 0.8f,		0.0f, 0.0f, 1.0f,	//front upper right	- index 2
	 0.8f, -0.8f, 0.8f,		1.0f, 1.0f, 1.0f,	//front lower right	- index 3

	-0.8f, -0.8f, -0.8f,	0.0f, 0.0f, 0.0f,	//back lower left	- index 4
	-0.8f,  0.8f, -0.8f,	1.0f, 0.0f, 1.0f,	//back upper left	- index 5
	 0.8f,  0.8f, -0.8f,	0.0f, 1.0f, 1.0f,	//back upper right	- index 6
	 0.8f, -0.8f, -0.8f,	1.0f, 1.0f, 0.0f	//back lower right	- index 7
};

//Basic 3D Cube indices
std::vector<unsigned int> indices{
	//front plane
	0, 1, 2,
	2, 3, 0,

	//back plane
	4, 5, 6,
	6, 7, 4,

	////top plane
	1, 5, 6,
	6, 2, 1,

	////bottom plane
	0, 4, 7,
	7, 3, 0,

	////right plane
	3, 2, 6,
	6, 7, 3,

	////left plane
	4, 5, 1,
	1, 0, 4
};

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

Mesh* ResourceManager::LoadBasicCubeMesh(std::string name)
{
	OpenGLMesh* mesh = new OpenGLMesh;

	m_Meshes[name] = mesh;

	VertexBufferLayout layout;
	layout.Push<float>(3); //Positions, location 0
	layout.Push<float>(3); //UV's,	location 1

	mesh->GetVertices() = vertices;
	mesh->GetLayout() = layout;
	mesh->GetIndices() = indices;
	mesh->CreateOpenGLData();

	return mesh;
}

const void ResourceManager::LoadBasicCube(std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	Mesh* mesh = LoadBasicCubeMesh(name);

	Entity* entity = new Entity(mesh, position, rotation, scale);
	m_Entities[name] = entity;
}
