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

ResourceManager* ResourceManager::m_Instance = 0; //Singleton

int main() {	
	// !! Create in this order !!
	DisplayManager displayManager(1280, 720, "Rendering Engine by Jeroen Schrader");
	InputManager inputManager(displayManager.GetWindow());
	Renderer renderer;
	GUI gui(displayManager.GetWindow());
	Camera camera(&inputManager, 0.1f, 0.3f, 90.0f, 0.01f, 1000.0f);
	ObjLoader loader;

	ResourceManager* resourceManager = resourceManager->GetInstance();
	resourceManager->LoadModel("Cube2", "res/models/Crate1.obj", &loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(0, 5, 3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Cube3", "res/models/Crate1.obj", &loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(10, 5, 3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Cube4", "res/models/Crate1.obj", &loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(0, 4, 15), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Cube5", "res/models/cubeTestMaterial.obj", &loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(-10, 3, 3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Cube6", "res/models/cubeTestMaterial.obj", &loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(-10, 3, 3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Cube7", "res/models/cubeTestMaterial.obj", &loader, "src/Shaders/BasicLightingShaderNoTexture.glsl", glm::vec3(0, 3, -10), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Wheel1", "res/models/PorscheWheelNormal.obj", &loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(3, 4, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Wheel2", "res/models/PorscheWheelNormal.obj", &loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(0, 2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Ground", "res/models/GroundTexture.obj", &loader, "src/Shaders/BasicLightingShader.glsl", glm::vec3(0, 0, 0), glm::vec3(0, 90, 0), glm::vec3(1, 1, 1));
	resourceManager->LoadModel("Light", "res/models/sphere.obj", &loader, "src/Shaders/LightSourceShader.glsl", glm::vec3(0, 2, 7), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	LightingInformation lightInformation;
	lightInformation.AmbientColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation.AmbientStrength = 0.1;
	lightInformation.DiffuseColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation.DiffuseStrength = 1.0;
	lightInformation.SpecularColor = glm::vec3(1.0, 1.0, 1.0);
	lightInformation.SpecularStrength = 0.0;

	/* Loop until the user closes the window or presses the Escape key */
	while (!inputManager.KeyPressed(GLFW_KEY_ESCAPE) && !displayManager.ShouldWindowClose())
	{
		inputManager.HandleInput();
		camera.Update();
		displayManager.Prepare();

		glm::mat4 projectionMatrix = camera.GetProjectionMatrix();
		glm::mat4 viewMatrix = camera.GetViewMatrix();
		glm::vec3 cameraPosition = camera.GetPosition();
		lightInformation.CameraPosition = cameraPosition;

		//Rotate light around the world
		Entity* light = resourceManager->GetEntityByName("Light");
		light->GetPosition().x = 1.0f + sin(glfwGetTime() * .3) * 20.0f;
		light->GetPosition().z = -cos(glfwGetTime() * .3) * 20.0f;
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

			renderer.Draw(entityP->GetMesh()->GetVertexIndexCount());
		}

		gui.OnGUIUpdate();
		displayManager.UpdateDisplay();
	}

	displayManager.~DisplayManager();
	inputManager.~InputManager();
	gui.Cleanup();

	return 0;
}