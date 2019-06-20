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
#include "PostProcessing.h"

//Initialize singletons
DisplayManager* DisplayManager::m_Instance = 0;
InputManager* InputManager::m_Instance = 0;
Renderer* Renderer::m_Instance = 0; 
ResourceManager* ResourceManager::m_Instance = 0;
Camera* Camera::m_Instance = 0;
ObjLoader* ObjLoader::m_Instance = 0;
SceneManager* SceneManager::m_Instance = 0;

std::string CurrentShader = "BasicShader.glsl";
const std::string MirrorShader = "MirrorShader.glsl";

int main() {	
	// !! Create in this order !!
	DisplayManager* displayManager = DisplayManager::GetInstance();
	InputManager* inputManager = InputManager::GetInstance();
	Renderer* renderer = Renderer::GetInstance();
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	Camera* camera = Camera::GetInstance();
	ObjLoader* loader = ObjLoader::GetInstance();
	GUI gui(displayManager->GetWindow());
	SceneManager* sceneManager = SceneManager::GetInstance();

	resourceManager->LoadModel("Mirror", "res/models/Mirror.obj", loader, "src/Shaders/" + MirrorShader, glm::vec3(15, 2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 3, 3));
	resourceManager->LoadModel("Light", "res/models/sphere.obj", loader, "src/Shaders/LightSourceShader.glsl", glm::vec3(-8, 8, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Ground", "res/models/Floor.obj", loader, "src/Shaders/" + CurrentShader, glm::vec3(0, -2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	
	Scene* currentScene = sceneManager->GetCurrentScene();
	LightingInformation* lightInformation = currentScene->m_LightInformation;
	Skybox* skybox = currentScene->m_Skybox;
	Entity* light = resourceManager->GetEntities()["Light"];

	gui.InitializeSceneGUI(currentScene);	

	PostProcessing* pp = resourceManager->CreatePostProcessingEffect("Effect1");
	Effects effects(&gui.GreyScaleEffectEnabled, &gui.InverseColorEffectEnabled);

	while (!inputManager->KeyPressed(GLFW_KEY_ESCAPE) && !displayManager->ShouldWindowClose())
	{
		inputManager->HandleInput();
		camera->Update();
		pp->InitializeFirstPass();
		glViewport(0, 0, 1280, 720);
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
				Entity* loadedModel = resourceManager->LoadModel(fileName.substr(0, fileName.size() - 4), dialog.GetFullFilePath(), loader, isMirrorObject ? "src/Shaders/" + MirrorShader : "src/Shaders/" + CurrentShader, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), isMirrorObject ? glm::vec3(1, 3, 3) : glm::vec3(1, 1, 1));
				gui.AddEntityToGUI(loadedModel);			
			}
			else {
				std::cout << dialog.GetErrorMessage() << std::endl;
			}
			gui.LoadModelButtonClicked = false;
		}

		if (gui.LoadNextSceneButtonClicked) {
			//Load next scene if arrow button is clicked
			currentScene = sceneManager->GetNextScene();
			lightInformation = currentScene->m_LightInformation;
			skybox = currentScene->m_Skybox;
			light = resourceManager->GetEntityByName("Light");
			Entity* ground = resourceManager->GetEntityByName("Ground");
			ground->SetNewTexture(currentScene->m_GroundTexture);

			gui.InitializeSceneGUI(currentScene);
			gui.LoadNextSceneButtonClicked = false;
		}

		//Draw Skybox
		skybox->Bind(projectionMatrix, viewMatrix);
		renderer->Draw(skyboxIndices.size());
		glDepthFunc(GL_LESS);

		//Render each entity in the world
		for(const auto& entity : resourceManager->GetEntities()){
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

		glViewport(0, 0, displayManager->GetWindowWidth(), displayManager->GetWindowHeight());
		pp->InitializeSecondPass(&effects);
		renderer->Draw(quadIndices.size());
	
		gui.OnGUIUpdate();
		displayManager->UpdateDisplay();
	}

	displayManager->~DisplayManager();
	inputManager->~InputManager();
	gui.Cleanup();
	resourceManager->~ResourceManager();

	return 0;
}