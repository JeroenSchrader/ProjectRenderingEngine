#include <iostream>

#include "Renderer.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "Camera.h"
#include "ResourceManager.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "OpenGLMesh.h"
#include "Entity.h"

int main() {	
	DisplayManager displayManager(1280, 720, "Rendering Engine by Jeroen Schrader");
	InputManager inputManager(displayManager.GetWindow());
	Renderer renderer;
	Camera camera(&inputManager, 0.1f, 0.7f, 90.0f, 0.01f, 1000.0f);

	ResourceManager resourceManager;

	resourceManager.LoadBasicCube("Mesh1", glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(1,1,1));
	resourceManager.LoadBasicCube("Mesh2", glm::vec3(2, 0, 0), glm::vec3(4, 0, 0), glm::vec3(1, 1, 1));
	resourceManager.LoadBasicCube("Mesh3", glm::vec3(6, 3, 0), glm::vec3(10, 0, 0), glm::vec3(1, 1, 1));
	resourceManager.LoadBasicCube("Mesh4", glm::vec3(2, -5, 0), glm::vec3(30, 0, 0), glm::vec3(1, 1, 1));
	resourceManager.LoadBasicCube("Mesh5", glm::vec3(3, 0, 6), glm::vec3(60, 0, 0), glm::vec3(1, 1, 1));

	//Todo: Create material class which contains a shader + uniform variables
	Shader shader("src/Shaders/BasicShader.shader");
	shader.Bind();
	
	/* Loop until the user closes the window or presses the Escape key */
	while (!inputManager.KeyPressed(GLFW_KEY_ESCAPE) && !displayManager.ShouldWindowClose())
	{
		inputManager.HandleInput();

		camera.Update();

		displayManager.Prepare();

		glm::mat4 viewMatrix = camera.GetViewMatrix();
		glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

		for(const auto& ent : resourceManager.GetEntities()){
			glm::mat4 transformationMatrix = ent.second->GetTransformationMatrix();

			//Todo: Create material class which contains a shader + uniform variables and bind them on draw
			shader.Bind();
			shader.SetUniformMatrix4f("u_transformationMatrix", transformationMatrix);
			shader.SetUniformMatrix4f("u_viewMatrix", viewMatrix);
			shader.SetUniformMatrix4f("u_projectionMatrix", projectionMatrix);

			renderer.Draw(ent.second->GetMesh()->GetVertexIndexCount());
		}

		displayManager.UpdateDisplay();
	}

	displayManager.~DisplayManager();
	inputManager.~InputManager();

	return 0;
}