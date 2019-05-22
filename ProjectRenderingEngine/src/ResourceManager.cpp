#include "ResourceManager.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include "GLM/vec3.hpp"

#include "ObjLoader.h"
#include "Entity.h"
#include "OpenGLMesh.h"

#include "Shader.h"
#include "Material.h"
#include "Texture.h"

Material* ResourceManager::LoadMaterial(std::string name, const std::string& shaderPath, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	Material* material = new Material(shaderPath, ambient, diffuse, specular, shininess);
	m_Materials[name] = material;

	return material;
}

Material* ResourceManager::LoadMaterial(std::string name, const std::string& shaderPath, glm::vec3 color, float shininess)
{
	Material* material = new Material(shaderPath, color, shininess);
	m_Materials[name] = material;

	return material;
}

const void ResourceManager::LoadModel(std::string name, std::string file, ObjLoader* loader, const std::string& shaderPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	ObjFileFormat format;

	loader->LoadMesh(file, vertices, indices, format);

	VertexBufferLayout layout;
	layout.Push<float>(3);		//Positions,	location 0
	if (format.HasTextures) {
		layout.Push<float>(2);	//UV's,			location 1
		layout.Push<float>(3);	//Tangents,		location 3 (! Normals are loaded first in the ObjLoader)
		layout.Push<float>(3);	//Bitangents,	location 4 (! Normals are loaded first in the ObjLoader)
	}
	layout.Push<float>(3);		//Normals,		location 2

	OpenGLMesh* mesh = new OpenGLMesh();
	m_Meshes[name] = mesh;

	mesh->GetVertices() = vertices;
	mesh->GetIndices() = indices;
	mesh->GetLayout() = layout;
	mesh->CreateOpenGLData();

	Texture* textureMap = new Texture();
	m_TextureMaps[name] = textureMap;

	Texture* normalMap = new Texture();
	m_NormalMaps[name] = normalMap;

	Material* material = LoadMaterial(name, shaderPath, glm::vec3(1.0,1.0,1.0), 128);
	loader->LoadMaterial(file.replace(file.end()-4, file.end(), ".mtl"), *material, *textureMap, *normalMap);

	Entity* entity = new Entity(name, mesh, material, textureMap, normalMap, position, rotation, scale);
	m_Entities[name] = entity;
}


