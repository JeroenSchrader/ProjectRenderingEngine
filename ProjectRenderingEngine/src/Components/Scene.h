#pragma once

#include <string>

class ResourceManager;
class LightingInformation;
class Skybox;
class Texture;

class Scene {
public:
	Scene() = default;
	~Scene() = default;

	LightingInformation* m_LightInformation;
	Skybox* m_Skybox;
	Texture* m_GroundTexture;

	inline std::string GetName() { return m_Name; }

private:
	std::string m_Name;
};