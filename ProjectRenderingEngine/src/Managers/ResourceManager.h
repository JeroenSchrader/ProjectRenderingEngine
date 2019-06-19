#pragma once

#include <map>
#include <string>
#include "GLM/vec3.hpp"

class OpenGLMesh;
class Material;
class Shader;
class Entity;
class ObjLoader;
class Texture;
class Cubemap;
class Skybox;

class ResourceManager {
private:
	static ResourceManager* m_Instance;
	ResourceManager() = default;

	std::map<std::string, OpenGLMesh*> m_Meshes;
	std::map<std::string, Entity*> m_Entities;
	std::map<std::string, Shader*> m_Shaders;
	std::map<std::string, Material*> m_Materials;
	std::map<std::string, Texture*> m_TextureMaps;
	std::map<std::string, Texture*> m_NormalMaps;
	std::map<std::string, Cubemap*> m_Cubemaps;
	std::map<std::string, Skybox*> m_Skyboxes;
public:
	static ResourceManager* GetInstance() {
		if (m_Instance) {
			return m_Instance;
		}
		m_Instance = new ResourceManager();
		return m_Instance;
	}

	~ResourceManager() = default;

	Material* LoadMaterial(std::string name, const std::string& shaderPath, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	Material* LoadMaterial(std::string name, const std::string& shaderPath, glm::vec3 color, float shininess);
	Entity* LoadModel(std::string name, std::string file, ObjLoader* loader, const std::string& shaderPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Skybox* LoadSkybox(std::string name, std::string filePath);
	Texture* LoadTextureMap(std::string name, std::string filePath);

	inline std::map<std::string, OpenGLMesh*> GetMeshes() const { return m_Meshes; }
	inline std::map<std::string, Entity*> GetEntities() const { return m_Entities; }
	inline std::map<std::string, Shader*> GetShaders() const { return m_Shaders; }
	inline std::map<std::string, Material*> GetMaterials() const { return m_Materials; }
	inline std::map<std::string, Texture*> GetTextureMaps() const { return m_TextureMaps; }
	inline std::map<std::string, Texture*> GetNormalMaps() const { return m_NormalMaps; }
	inline std::map<std::string, Cubemap*> GetCubemaps() const { return m_Cubemaps; }
	inline std::map<std::string, Skybox*> GetSkyboxes() const { return m_Skyboxes; }

	inline OpenGLMesh* GetMeshByName(std::string name) { return m_Meshes[name]; }
	inline Entity* GetEntityByName(std::string name) { return m_Entities[name]; }
	inline Material* GetMaterialByName(std::string name) { return m_Materials[name]; }
	inline Texture* GetTextureMapByName(std::string name) { return m_TextureMaps[name]; }
	inline Texture* GetNormalMapByName(std::string name) { return m_NormalMaps[name]; }
};
