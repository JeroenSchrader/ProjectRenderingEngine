#pragma once

#include <map>
#include <string>
#include "GLM/vec3.hpp"

class OpenGLMesh;
class Material;
class Entity;
class ObjLoader;

class ResourceManager {
private:
	std::map<std::string, OpenGLMesh*> m_Meshes;
	std::map<std::string, Entity*> m_Entities;
	std::map<std::string, Material*> m_Materials;
public:
	ResourceManager() = default;
	~ResourceManager() = default;

	OpenGLMesh* LoadBasicCubeMesh(std::string name);
	Material* LoadMaterial(std::string name, const std::string& shaderPath);
	const void LoadBasicCube(std::string name, const std::string& shaderPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	const void LoadModel(std::string name, std::string file, ObjLoader* loader, const std::string& shaderPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	std::map<std::string, OpenGLMesh*> GetMeshes() const { return m_Meshes; }
	std::map<std::string, Entity*> GetEntities() const { return m_Entities; }
	std::map<std::string, Material*> GetMaterials() const { return m_Materials; }
};
