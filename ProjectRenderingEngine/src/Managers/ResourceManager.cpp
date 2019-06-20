#include "ResourceManager.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "FrameBuffer.h"

#include "GLM/vec3.hpp"

#include "ObjLoader.h"
#include "Entity.h"
#include "OpenGLMesh.h"

#include "Shader.h"
#include "Material.h"
#include "Texture.h"

#include "Cubemap.h"
#include "Skybox.h"
#include "PostProcessing.h"

#include <fstream>
#include <iostream>

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

Entity* ResourceManager::LoadModel(std::string name, std::string file, ObjLoader* loader, const std::string& shaderPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	ObjFileFormat format;

	std::ifstream stream(file);
	loader->LoadMesh(stream, vertices, indices, format);

	VertexBufferLayout layout;
	layout.Push<float>(3);		//Positions,	location 0
	if (format.HasTextures) {
		layout.Push<float>(2);	//UV/Textures,	location 1
		layout.Push<float>(3);	//Tangents,		location 3 (! Normals are loaded first in the ObjLoader)
		layout.Push<float>(3);	//Bitangents,	location 4 (! Normals are loaded first in the ObjLoader)
	}
	layout.Push<float>(3);		//Normals,		location 2

	OpenGLMesh* mesh = new OpenGLMesh();

	int lastEntity = -1;
	std::string newName = name;

	for (auto const& element : m_Meshes)
	{
		//Check all mesh names. If one with the same name exists create one with 1, 2, 3 etc.. at the end
		//Example: if Tree1 exists, create a new one with name Tree1_1. And Tree1_2 afterwards
		const std::string key = element.first;
		if (key.find(name) == std::string::npos) {
			continue;
		}
		std::string substr = key.substr(key.size() - 2, 2);
		if (substr.find("_") != std::string::npos) {
			int entityNr = std::stoi(substr.substr(1, 1));
			if (entityNr > lastEntity) {
				lastEntity = entityNr;
			}
		}
		else {
			newName += "_" + std::to_string(1);
		}
	}
	if (lastEntity != -1) {
		newName = newName.replace(newName.size() - 1, 1, std::to_string(lastEntity + 1));
	}

	m_Meshes[newName] = mesh;

	mesh->GetVertices() = vertices;
	mesh->GetIndices() = indices;
	mesh->GetLayout() = layout;
	mesh->CreateOpenGLData();

	Texture* textureMap = new Texture();
	m_TextureMaps[newName] = textureMap;

	Texture* normalMap = new Texture();
	m_NormalMaps[newName] = normalMap;

	Material* material = LoadMaterial(newName, shaderPath, glm::vec3(1.0,1.0,1.0), 128);
	loader->LoadMaterial(file.replace(file.end()-4, file.end(), ".mtl"), *material, *textureMap, *normalMap);

	Entity* entity = new Entity(newName, mesh, material, textureMap, normalMap, position, rotation, scale);
	m_Entities[newName] = entity;

	return entity;
}

Skybox* ResourceManager::LoadSkybox(std::string name, std::string filePath)
{
	Cubemap* cubemap = new Cubemap(filePath);
	m_Cubemaps[name] = cubemap;

	Shader* shader = new Shader("src/Shaders/Effects/SkyboxShader.glsl");
	m_Shaders[name] = shader;

	VertexBufferLayout layout;
	layout.Push<float>(3);		//Positions,	location 0

	OpenGLMesh* mesh = new OpenGLMesh();
	m_Meshes[name] = mesh;

	mesh->GetVertices() = skyboxVertices;
	mesh->GetIndices() = skyboxIndices;
	mesh->GetLayout() = layout;
	mesh->CreateOpenGLData();

	Skybox* skybox = new Skybox(cubemap, shader, mesh);
	m_Skyboxes[name] = skybox;

	return skybox;
}

Texture* ResourceManager::LoadTextureMap(std::string name, std::string filePath)
{
	Texture* textureMap = new Texture();
	m_TextureMaps[name] = textureMap;

	textureMap->LoadNewTexture(filePath, TextureTypes::TextureMap);

	return textureMap;
}

PostProcessing* ResourceManager::CreatePostProcessingEffect(std::string name)
{
	Shader* shader = new Shader("src/Shaders/Effects/QuadShader.glsl");
	m_Shaders[name] = shader;

	VertexBufferLayout layout;
	layout.Push<float>(2);	//Positions,	location 0
	layout.Push<float>(2);	//Textures,		location 1

	OpenGLMesh* mesh = new OpenGLMesh();
	m_Meshes[name] = mesh;

	mesh->GetVertices() = quadVertices;
	mesh->GetIndices() = quadIndices;
	mesh->GetLayout() = layout;
	mesh->CreateOpenGLData();

	FrameBuffer* fbo = new FrameBuffer();
	m_FrameBuffers[name] = fbo;

	PostProcessing* effect = new PostProcessing(fbo, shader, mesh);
	m_PostProcessingEffects[name] = effect;

	return effect;
}

