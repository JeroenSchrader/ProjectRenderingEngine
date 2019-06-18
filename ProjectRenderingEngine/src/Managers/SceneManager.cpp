#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "ObjLoader.h"

SceneManager::SceneManager() : m_CurrentShader("BasicShader.glsl")
{
	LoadIceScene();
	LoadOceanScene();
	LoadSunsetScene();
}

void SceneManager::LoadIceScene()
{
	ObjLoader* loader = ObjLoader::GetInstance();

	Scene* scene = new Scene();

	ResourceManager* resourceManager = new ResourceManager();
	resourceManager->LoadModel("Mirror", "res/models/Mirror.obj", loader, "src/Shaders/" + m_MirrorShader, glm::vec3(15, 2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 3, 3));
	resourceManager->LoadModel("Light", "res/models/sphere.obj", loader, "src/Shaders/LightSourceShader.glsl", glm::vec3(-8, 8, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Ground", "res/models/IceFloor.obj", loader, "src/Shaders/" + m_CurrentShader, glm::vec3(0, -2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	scene->m_ResourceManager = resourceManager;

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

	m_Scenes.push_back(scene);
	m_SceneIterator = m_Scenes.begin();
}

void SceneManager::LoadOceanScene()
{
	ObjLoader* loader = ObjLoader::GetInstance();

	Scene* scene = new Scene();

	ResourceManager* resourceManager = new ResourceManager();
	resourceManager->LoadModel("Mirror", "res/models/Mirror.obj", loader, "src/Shaders/" + m_MirrorShader, glm::vec3(15, 4, 0), glm::vec3(0, 0, 0), glm::vec3(1, 3, 3));
	resourceManager->LoadModel("Light", "res/models/sphere.obj", loader, "src/Shaders/LightSourceShader.glsl", glm::vec3(12, 8, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Ground", "res/models/GroundTexture.obj", loader, "src/Shaders/" + m_CurrentShader, glm::vec3(0, -2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	scene->m_ResourceManager = resourceManager;

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

	m_Scenes.push_back(scene);
	m_SceneIterator = m_Scenes.begin();
}

void SceneManager::LoadSunsetScene()
{
	ObjLoader* loader = ObjLoader::GetInstance();

	Scene* scene = new Scene();

	ResourceManager* resourceManager = new ResourceManager();
	resourceManager->LoadModel("Mirror", "res/models/Mirror.obj", loader, "src/Shaders/" + m_MirrorShader, glm::vec3(15, 4, 0), glm::vec3(0, 0, 0), glm::vec3(1, 3, 3));
	resourceManager->LoadModel("Tree", "res/models/PineTree.obj", loader, "src/Shaders/" + m_MirrorShader, glm::vec3(15, -2, 15), glm::vec3(0, 0, 0), glm::vec3(4, 4, 4));
	resourceManager->LoadModel("Light", "res/models/sphere.obj", loader, "src/Shaders/LightSourceShader.glsl", glm::vec3(12, 8, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Ground", "res/models/BeachFloor.obj", loader, "src/Shaders/" + m_CurrentShader, glm::vec3(0, -2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	scene->m_ResourceManager = resourceManager;

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

	m_Scenes.push_back(scene);
	m_SceneIterator = m_Scenes.begin();
}
