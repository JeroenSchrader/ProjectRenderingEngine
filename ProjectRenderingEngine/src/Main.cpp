#include <iostream>

#include "Renderer.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ObjLoader.h"
#include "GUI.h"
#include "FileDialog.h"

#include "OpenGLMesh.h"
#include "Entity.h"
#include "Skybox.h"
#include "Scene.h"

//Initialize singletons
DisplayManager* DisplayManager::m_Instance = 0;
InputManager* InputManager::m_Instance = 0;
Renderer* Renderer::m_Instance = 0; 
Camera* Camera::m_Instance = 0;
ObjLoader* ObjLoader::m_Instance = 0;
SceneManager* SceneManager::m_Instance = 0;

std::string CurrentShader = "BasicShader.glsl";
const std::string MirrorShader = "MirrorShader.glsl";
//std::string CurrentShader = "BasicShader_NormalMapping.glsl";

int main() {	
	// !! Create in this order !!
	DisplayManager* displayManager = DisplayManager::GetInstance();
	InputManager* inputManager = InputManager::GetInstance();
	Renderer* renderer = Renderer::GetInstance();
	Camera* camera = Camera::GetInstance();
	ObjLoader* loader = ObjLoader::GetInstance();
	GUI gui(displayManager->GetWindow());
	SceneManager* sceneManager = SceneManager::GetInstance();

	Scene* currentScene = sceneManager->GetCurrentScene();
	LightingInformation* lightInformation = currentScene->m_LightInformation;
	ResourceManager* resourceManager = currentScene->m_ResourceManager;
	Skybox* skybox = currentScene->m_Skybox;
	Entity* light = resourceManager->GetEntities()["Light"];

	gui.InitializeSceneGUI(currentScene);

	while (!inputManager->KeyPressed(GLFW_KEY_ESCAPE) && !displayManager->ShouldWindowClose())
	{
		inputManager->HandleInput();
		camera->Update();
		displayManager->Prepare();

		glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
		glm::mat4 viewMatrix = camera->GetViewMatrix();
		glm::vec3 cameraPosition = camera->GetPosition();
		lightInformation->CameraPosition = cameraPosition;
		lightInformation->Position = light->GetPosition();

		if (gui.LoadModelButtonClicked) {
			//Open windows file dialog, load model and add to GUI

			FileDialog dialog;
			if (dialog.Open() != -1) {
				std::string fileName = dialog.GetFileName();
				//Remove .obj from fileName
				bool isMirrorObject = fileName.find("Mirror") != std::string::npos;
				Entity* loadedModel = resourceManager->LoadModel(fileName.substr(0, fileName.size() - 4), dialog.GetFullFilePath(), loader, isMirrorObject ? "src/Shaders/" + MirrorShader : "src/Shaders/" + CurrentShader, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), isMirrorObject ? glm::vec3(1, 3, 3) : glm::vec3(1,1,1));
				gui.AddEntityToGUI(loadedModel);			
			}
			else {
				std::cout << dialog.GetErrorMessage() << std::endl;
			}
			gui.LoadModelButtonClicked = false;
		}

		if (gui.LoadNextSceneButtonClicked) {
			//If arrow button is clicked, load next scene
			currentScene = sceneManager->GetNextScene();
			lightInformation = currentScene->m_LightInformation;
			resourceManager = currentScene->m_ResourceManager;
			skybox = currentScene->m_Skybox;
			light = resourceManager->GetEntities()["Light"];

			gui.InitializeSceneGUI(currentScene);
			gui.LoadNextSceneButtonClicked = false;
		}

		skybox->Bind(projectionMatrix, viewMatrix);
		renderer->Draw(skyboxIndices.size());
		glDepthFunc(GL_LESS);

		for(const auto& entity : resourceManager->GetEntities()){
			//Render each entity in the world
			Entity* entityP = entity.second;
			entityP->Bind();
			if (entityP->GetName().find("Light") == std::string::npos) {
				entityP->SetLightingInformation(*lightInformation);
			}

			entityP->SetProjectionMatrix(projectionMatrix);
			entityP->SetViewMatrix(viewMatrix);
			glm::mat4 transformationMatrix = entityP->GetTransformationMatrix();
			entityP->SetTransformationMatrix(transformationMatrix);

			renderer->Draw(entityP->GetMesh()->GetVertexIndexCount());
		}

		gui.OnGUIUpdate();
		displayManager->UpdateDisplay();
	}

	displayManager->~DisplayManager();
	inputManager->~InputManager();
	gui.Cleanup();
	resourceManager->~ResourceManager();

	return 0;
}