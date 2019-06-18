#pragma once

#include <string>

class ResourceManager;
class LightingInformation;
class Skybox;

class Scene {
public:
	Scene() = default;
	~Scene() = default;

	ResourceManager* m_ResourceManager;
	LightingInformation* m_LightInformation;
	Skybox* m_Skybox;

	inline std::string GetName() { return m_Name; }

private:
	std::string m_Name;
};