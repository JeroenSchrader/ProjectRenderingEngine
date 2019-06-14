#include <iostream>

#include "Renderer.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "ObjLoader.h"
#include "GUI.h"
#include "FileDialog.h"

#include "OpenGLMesh.h"
#include "Entity.h"
#include "Skybox.h"

//Initialize singletons
DisplayManager* DisplayManager::m_Instance = 0;
InputManager* InputManager::m_Instance = 0;
Renderer* Renderer::m_Instance = 0; 
ResourceManager* ResourceManager::m_Instance = 0; 
Camera* Camera::m_Instance = 0;
ObjLoader* ObjLoader::m_Instance = 0;

const float MaxEntityPosition = 15.0f;
const float MaxEntityRotation = 360.0f;
const float MaxRGBColorRange = 1.0f;
std::string CurrentShader = "BasicShader.glsl";
//std::string CurrentShader = "BasicShader_NormalMapping.glsl";

int main() {	
	// !! Create in this order !!
	DisplayManager* displayManager = DisplayManager::GetInstance();
	InputManager* inputManager = InputManager::GetInstance();
	Renderer* renderer = Renderer::GetInstance();
	Camera* camera = Camera::GetInstance();
	ObjLoader* loader = ObjLoader::GetInstance();
	GUI gui(displayManager->GetWindow());
	ResourceManager* resourceManager = resourceManager->GetInstance();

	resourceManager->LoadModel("Cube", "res/models/testCubeTexture.obj", loader, "src/Shaders/" + CurrentShader, glm::vec3(0, 2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Wheel", "res/models/PorscheWheelNormal.obj", loader, "src/Shaders/" + CurrentShader, glm::vec3(0, 2, 2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Light", "res/models/sphere.obj", loader, "src/Shaders/LightSourceShader.glsl", glm::vec3(-8, 8, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Ground", "res/models/BrickWall.obj", loader, "src/Shaders/" + CurrentShader, glm::vec3(0, -2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	LightingInformation lightInformation;
	lightInformation.AmbientColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation.AmbientStrength = 0.35;
	lightInformation.DiffuseColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation.DiffuseStrength = 1.0;
	lightInformation.SpecularColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation.SpecularStrength = 1.0;

	gui.AddFloat3("Ambient Light Color", &lightInformation.AmbientColor.x, 0, MaxRGBColorRange);
	gui.AddFloat1("Ambient Light Strength", &lightInformation.AmbientStrength, 0, MaxRGBColorRange);
	gui.AddFloat3("Diffuse Light Color", &lightInformation.DiffuseColor.x, 0, MaxRGBColorRange);
	gui.AddFloat1("Diffuse Light Strength", &lightInformation.DiffuseStrength, 0, MaxRGBColorRange);
	gui.AddFloat3("Specular Light Color", &lightInformation.SpecularColor.x, 0, MaxRGBColorRange);
	gui.AddFloat1("Specular Light Strength", &lightInformation.SpecularStrength, 0, MaxRGBColorRange);

	std::map<std::string, Entity*> entities = resourceManager->GetEntities();
	for (std::map<std::string, Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		//Add all GUI items for each entity in the world
		gui.AddFloat3(it->first, &it->second->GetPosition().x, -MaxEntityPosition, MaxEntityPosition);
		gui.AddFloat3(it->first + " Rotation", &it->second->GetRotation().x, 0, MaxEntityRotation);
	}

	Entity* light = entities["Light"];
	Skybox* skybox = resourceManager->LoadSkybox("Ocean", "res/cubemaps/ocean");

	while (!inputManager->KeyPressed(GLFW_KEY_ESCAPE) && !displayManager->ShouldWindowClose())
	{
		inputManager->HandleInput();
		camera->Update();
		displayManager->Prepare();

		glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
		glm::mat4 viewMatrix = camera->GetViewMatrix();
		glm::vec3 cameraPosition = camera->GetPosition();
		lightInformation.CameraPosition = cameraPosition;
		lightInformation.Position = light->GetPosition();

		if (gui.LoadModelButtonClicked) {
			//Open windows file dialog, load model and add to GUI

			FileDialog dialog;
			if (dialog.Open() != -1) {
				std::string fileName = dialog.GetFileName();
				//Remove .obj from fileName
				Entity* loadedModel = resourceManager->LoadModel(fileName.substr(0, fileName.size() - 4), dialog.GetFullFilePath(), loader, "src/Shaders/" + CurrentShader, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
				gui.AddFloat3(loadedModel->GetName(), &loadedModel->GetPosition().x, -MaxEntityPosition, MaxEntityPosition);
				gui.AddFloat3(loadedModel->GetName() + " Rotation", &loadedModel->GetRotation().x, 0, MaxEntityRotation);
			}
			else {
				std::cout << dialog.GetErrorMessage() << std::endl;
			}
			gui.LoadModelButtonClicked = false;
		}

		skybox->Bind(projectionMatrix, viewMatrix);
		renderer->Draw(skyboxIndices.size());
		glDepthFunc(GL_LESS);

		for(const auto& entity : resourceManager->GetEntities()){
			//Render each entity in the world
			Entity* entityP = entity.second;
			entityP->Bind();
			if (entityP->GetName().find("Light") == std::string::npos) {
				entityP->SetLightingInformation(lightInformation);
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

	return 0;
}