#include "ResourceManager.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include "ObjLoader.h"
#include "Entity.h"
#include "OpenGLMesh.h"

#include "Shader.h"
#include "Material.h"

//Basic 3D Cube vertices
std::vector<float> cubeVertices{
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
std::vector<unsigned int> cubeIndices{
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

OpenGLMesh* ResourceManager::LoadBasicCubeMesh(std::string name)
{
	OpenGLMesh* mesh = new OpenGLMesh();

	m_Meshes[name] = mesh;

	VertexBufferLayout layout;
	layout.Push<float>(3); //Positions, location 0
	layout.Push<float>(3); //UV's,	location 1

	mesh->GetVertices() = cubeVertices;
	mesh->GetLayout() = layout;
	mesh->GetIndices() = cubeIndices;
	mesh->CreateOpenGLData();

	return mesh;
}

Material* ResourceManager::LoadMaterial(std::string name, const std::string& shaderPath)
{
	Material* material = new Material(shaderPath);
	m_Materials[name] = material;

	return material;
}

const void ResourceManager::LoadBasicCube(std::string name, const std::string& shaderPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	OpenGLMesh* mesh = LoadBasicCubeMesh(name);
	Material* material = LoadMaterial(name, shaderPath);

	Entity* entity = new Entity(name, mesh, material, position, rotation, scale);
	m_Entities[name] = entity;
}

const void ResourceManager::LoadModel(std::string name, std::string file, ObjLoader* loader, const std::string& shaderPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	ObjFileFormat format;

	loader->Load(file, vertices, indices, format);

	VertexBufferLayout layout;
	layout.Push<float>(3); //Positions, location 0
	if (format.HasTextures) {
		layout.Push<float>(2); //UV's,		location 1
	}
	if (format.HasNormals) {
		layout.Push<float>(3); //Normals,	location 2
	}
	
	OpenGLMesh* mesh = new OpenGLMesh();
	m_Meshes[name] = mesh;

	mesh->GetVertices() = vertices;
	mesh->GetIndices() = indices;
	mesh->GetLayout() = layout;
	mesh->CreateOpenGLData();

	Material* material = LoadMaterial(name, shaderPath);

	Entity* entity = new Entity(name, mesh, material, position, rotation, scale);	
	m_Entities[name] = entity;
}


