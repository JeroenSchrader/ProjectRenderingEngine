#pragma once

#include <map>
#include <string>
#include "GLM/vec3.hpp"

class Mesh;
class Shader;
class Entity;

class ResourceManager {
private:
	std::map<std::string, Mesh*> m_Meshes;
	std::map<std::string, Entity*> m_Entities;
	std::map<std::string, Shader*> m_Shaders;
public:
	ResourceManager();
	~ResourceManager();

	Mesh* LoadBasicCubeMesh(std::string name);
	const void LoadBasicCube(std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	std::map<std::string, Mesh*> GetMeshes() const { return m_Meshes; }
	std::map<std::string, Entity*> GetEntities() const { return m_Entities; }
};
