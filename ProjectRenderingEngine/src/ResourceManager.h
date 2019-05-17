#pragma once

#include <map>
#include <string>
#include "GLM/vec3.hpp"

class OpenGLMesh;
class Material;
class Entity;
class ObjLoader;
class Texture;

class ResourceManager {
private:
	std::map<std::string, OpenGLMesh*> m_Meshes;
	std::map<std::string, Entity*> m_Entities;
	std::map<std::string, Material*> m_Materials;
	std::map<std::string, Texture*> m_TextureMaps;
	std::map<std::string, Texture*> m_NormalMaps;
public:
	ResourceManager() = default;
	~ResourceManager() = default;

	Material* LoadMaterial(std::string name, const std::string& shaderPath, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	Material* LoadMaterial(std::string name, const std::string& shaderPath, glm::vec3 color, float shininess);
	const void LoadModel(std::string name, std::string file, ObjLoader* loader, const std::string& shaderPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	inline std::map<std::string, OpenGLMesh*> GetMeshes() const { return m_Meshes; }
	inline std::map<std::string, Entity*> GetEntities() const { return m_Entities; }
	inline std::map<std::string, Material*> GetMaterials() const { return m_Materials; }
	inline std::map<std::string, Texture*> GetTextureMaps() const { return m_TextureMaps; }
	inline std::map<std::string, Texture*> GetNormalMaps() const { return m_NormalMaps; }

	inline OpenGLMesh* GetMeshByName(std::string name) { return m_Meshes[name]; }
	inline Entity* GetEntityByName(std::string name) { return m_Entities[name]; }
	inline Material* GetMaterialByName(std::string name) { return m_Materials[name]; }
	inline Texture* GetTextureMapByName(std::string name) { return m_TextureMaps[name]; }
	inline Texture* GetNormalMapByName(std::string name) { return m_NormalMaps[name]; }
};
