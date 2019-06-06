#include <iostream>

#include "Renderer.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "ObjLoader.h"
#include "GUI.h"

#include "OpenGLMesh.h"
#include "Entity.h"

//Initialize singletons
DisplayManager* DisplayManager::m_Instance = 0;
InputManager* InputManager::m_Instance = 0;
Renderer* Renderer::m_Instance = 0; 
ResourceManager* ResourceManager::m_Instance = 0; 
Camera* Camera::m_Instance = 0;
ObjLoader* ObjLoader::m_Instance = 0;

int main() {	
	// !! Create in this order !!
	DisplayManager* displayManager = DisplayManager::GetInstance();
	InputManager* inputManager = InputManager::GetInstance();
	Renderer* renderer = Renderer::GetInstance();
	Camera* camera = Camera::GetInstance();
	ObjLoader* loader = ObjLoader::GetInstance();
	GUI gui(displayManager->GetWindow());
	ResourceManager* resourceManager = resourceManager->GetInstance();

	resourceManager->LoadModel("Cube2", "res/models/Crate1.obj", loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(0, 4, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Wheel1", "res/models/PorscheWheelNormal.obj", loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(0, 2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Wheel2", "res/models/PorscheWheelNormal.obj", loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Ground", "res/models/GroundTexture.obj", loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(0, -2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Light", "res/models/sphere.obj", loader, "src/Shaders/LightSourceShader.glsl", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	LightingInformation lightInformation;
	lightInformation.AmbientColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation.AmbientStrength = 0.1;
	lightInformation.DiffuseColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation.DiffuseStrength = 1.0;
	lightInformation.SpecularColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation.SpecularStrength = 1.0;

	Entity* light = resourceManager->GetEntityByName("Light");
	gui.AddFloat3("Light Position", &light->GetPosition().x, -15.0f, 15.0f);

	/* Loop until the user closes the window or presses the Escape key */
	while (!inputManager->KeyPressed(GLFW_KEY_ESCAPE) && !displayManager->ShouldWindowClose())
	{
		inputManager->HandleInput();
		camera->Update();
		displayManager->Prepare();

		glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
		glm::mat4 viewMatrix = camera->GetViewMatrix();
		glm::vec3 cameraPosition = camera->GetPosition();
		lightInformation.CameraPosition = cameraPosition;

		//Set new light position
		lightInformation.Position = light->GetPosition();

		for(const auto& entity : resourceManager->GetEntities()){
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