#include <iostream>

#include "Renderer.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "Camera.h"
#include "ResourceManager.h"

#include "OpenGLMesh.h"
#include "Entity.h"

int main() {	
	// !! Create in this order !!
	DisplayManager displayManager(1280, 720, "Rendering Engine by Jeroen Schrader");
	InputManager inputManager(displayManager.GetWindow());
	Renderer renderer;
	Camera camera(&inputManager, 0.1f, 0.7f, 90.0f, 0.01f, 1000.0f);

	ResourceManager resourceManager;
	resourceManager.LoadBasicCube("Cube1", "src/Shaders/BasicShader.shader", glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(1,1,1));
	resourceManager.LoadBasicCube("Cube2", "src/Shaders/BasicShader.shader", glm::vec3(2, 0, 0), glm::vec3(4, 0, 0), glm::vec3(1, 1, 1));
	resourceManager.LoadBasicCube("Cube3", "src/Shaders/TestShader.shader", glm::vec3(6, 3, 0), glm::vec3(10, 0, 0), glm::vec3(1, 1, 1));
	resourceManager.LoadBasicCube("Cube4", "src/Shaders/TestShader.shader", glm::vec3(2, -5, 0), glm::vec3(30, 0, 0), glm::vec3(1, 1, 1));
	resourceManager.LoadBasicCube("Cube5", "src/Shaders/BasicShader.shader", glm::vec3(3, 0, 6), glm::vec3(60, 0, 0), glm::vec3(1, 1, 1));
	
	/* Loop until the user closes the window or presses the Escape key */
	while (!inputManager.KeyPressed(GLFW_KEY_ESCAPE) && !displayManager.ShouldWindowClose())
	{
		inputManager.HandleInput();
		camera.Update();
		displayManager.Prepare();

		glm::mat4 projectionMatrix = camera.GetProjectionMatrix();
		glm::mat4 viewMatrix = camera.GetViewMatrix();

		for(const auto& entity : resourceManager.GetEntities()){
			Entity* entityP = entity.second;

			//Todo: Save uniform variables in Material class 
			entityP->BindMaterial();
			entityP->SetProjectionMatrix(projectionMatrix);
			entityP->SetViewMatrix(viewMatrix);

			glm::mat4 transformationMatrix = entityP->GetTransformationMatrix();
			entityP->SetTransformationMatrix(transformationMatrix);

			renderer.Draw(entityP->GetMesh()->GetVertexIndexCount());
		}

		displayManager.UpdateDisplay();
	}

	displayManager.~DisplayManager();
	inputManager.~InputManager();

	return 0;
}