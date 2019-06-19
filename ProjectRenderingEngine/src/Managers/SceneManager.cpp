#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "ObjLoader.h"

SceneManager::SceneManager()
{
	LoadIceScene();
	LoadOceanScene();
	LoadSunsetScene();
}

void SceneManager::LoadIceScene()
{
	ObjLoader* loader = ObjLoader::GetInstance();
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	Scene* scene = new Scene();

	LightingInformation* lightInformation = new LightingInformation();
	lightInformation->AmbientColor = glm::vec3(0.2, 0.5, 0.8);
	lightInformation->AmbientStrength = 0.35;
	lightInformation->DiffuseColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation->DiffuseStrength = 1.0;
	lightInformation->SpecularColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation->SpecularStrength = 1.0;
	scene->m_LightInformation = lightInformation;

	Skybox* skybox = resourceManager->LoadSkybox("Ice", "res/cubemaps/ice");
	scene->m_Skybox = skybox;

	Texture* groundTexture = resourceManager->LoadTextureMap("IceGroundTexture", "res/textures/ice.jpg");
	scene->m_GroundTexture = groundTexture;

	m_Scenes.push_back(scene);
	m_SceneIterator = m_Scenes.begin();
}

void SceneManager::LoadOceanScene()
{
	ObjLoader* loader = ObjLoader::GetInstance();
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	Scene* scene = new Scene();

	LightingInformation* lightInformation = new LightingInformation();
	lightInformation->AmbientColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation->AmbientStrength = 0.35;
	lightInformation->DiffuseColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation->DiffuseStrength = 1.0;
	lightInformation->SpecularColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation->SpecularStrength = 1.0;
	scene->m_LightInformation = lightInformation;

	Skybox* skybox = resourceManager->LoadSkybox("Ocean", "res/cubemaps/ocean");
	scene->m_Skybox = skybox;

	Texture* groundTexture = resourceManager->LoadTextureMap("OceanGroundTexture", "res/textures/GroundTexture.jpg");
	scene->m_GroundTexture = groundTexture;

	m_Scenes.push_back(scene);
	m_SceneIterator = m_Scenes.begin();
}

void SceneManager::LoadSunsetScene()
{
	ObjLoader* loader = ObjLoader::GetInstance();
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	Scene* scene = new Scene();

	LightingInformation* lightInformation = new LightingInformation();
	lightInformation->AmbientColor = glm::vec3(1.0, 0.3, 0.1);
	lightInformation->AmbientStrength = 0.35;
	lightInformation->DiffuseColor = glm::vec3(1.0, 0.9, 0.9);
	lightInformation->DiffuseStrength = 1.0;
	lightInformation->SpecularColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation->SpecularStrength = 1.0;
	scene->m_LightInformation = lightInformation;

	Skybox* skybox = resourceManager->LoadSkybox("Sunset", "res/cubemaps/sunset");
	scene->m_Skybox = skybox;

	Texture* groundTexture = resourceManager->LoadTextureMap("SunsetGroundTexture", "res/textures/beach.jpg");
	scene->m_GroundTexture = groundTexture;

	m_Scenes.push_back(scene);
	m_SceneIterator = m_Scenes.begin();
}
