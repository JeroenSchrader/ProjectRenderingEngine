#pragma once

#include <map>
#include <string>
#include "GLM/vec3.hpp"

class Mesh;
class Material;
class Entity;

class ResourceManager {
private:
	std::map<std::string, Mesh*> m_Meshes;
	std::map<std::string, Entity*> m_Entities;
	std::map<std::string, Material*> m_Materials;
public:
	ResourceManager() = default;
	~ResourceManager() = default;

	Mesh* LoadBasicCubeMesh(std::string name);
	Material* LoadMaterial(std::string name, const std::string& shaderPath);
	const void LoadBasicCube(std::string name, const std::string& shaderPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	std::map<std::string, Mesh*> GetMeshes() const { return m_Meshes; }
	std::map<std::string, Entity*> GetEntities() const { return m_Entities; }
	std::map<std::string, Material*> GetMaterials() const { return m_Materials; }
};
