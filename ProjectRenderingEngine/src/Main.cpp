#include <iostream>

#include "Renderer.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "Camera.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "RawModel.h"
#include "Entity.h"

int main() {	
	DisplayManager displayManager(1280, 720, "Rendering Engine by Jeroen Schrader");
	InputManager inputManager(displayManager.GetWindow());
	Renderer renderer;
	Camera camera(&inputManager, 0.1f, 0.7f, 90.0f, 0.01f, 1000.0f);

	//3D Rectangle vertices
	float vertices[]{
		//Positions				//Colors
		-0.8f, -0.8f, 0.8f,		0.0f, 1.0f, 0.0f,	//front lower left	- index 0
		-0.8f,  0.8f, 0.8f,		1.0f, 0.0f, 0.0f,	//front upper left	- index 1
		 0.8f,  0.8f, 0.8f,		0.0f, 0.0f, 1.0f,	//front upper right	- index 2
		 0.8f, -0.8f, 0.8f,		1.0f, 1.0f, 1.0f,	//front lower right	- index 3

		-0.8f, -0.8f, -0.8f,	0.0f, 0.0f, 0.0f,	//back lower left	- index 4
		-0.8f,  0.8f, -0.8f,	1.0f, 0.0f, 1.0f,	//back upper left	- index 5
		 0.8f,  0.8f, -0.8f,	0.0f, 1.0f, 1.0f,	//back upper right	- index 6
		 0.8f, -0.8f, -0.8f,	1.0f, 1.0f, 0.0f	//back lower right	- index 7
	};

	unsigned int indices[]{
		//front plane
		0, 1, 2,
		2, 3, 0,

		//back plane
		4, 5, 6,
		6, 7, 4,

		////top plane
		1, 5, 6,
		6, 2, 1,

		////bottom plane
		0, 4, 7,
		7, 3, 0,

		////right plane
		3, 2, 6,
		6, 7, 3,

		////left plane
		4, 5, 1,
		1, 0, 4
	};

	VertexBuffer vb(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3); //Positions, location 0
	layout.Push<float>(3); //Colors,	location 1

	VertexArray vao;	
	vao.AddBuffer(vb, layout);

	IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

	RawModel model(vao.GetId(), ib.GetCount());
	Entity entity(model, glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(1,1,1));
	Entity entity2(model, glm::vec3(2, 0, 0), glm::vec3(4, 0, 0), glm::vec3(1, 1, 1));

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

		{	
			glm::mat4 transformationMatrix = entity.GetTransformationMatrix();

			shader.Bind();
			shader.SetUniformMatrix4f("u_transformationMatrix", transformationMatrix);
			shader.SetUniformMatrix4f("u_viewMatrix", viewMatrix);
			shader.SetUniformMatrix4f("u_projectionMatrix", projectionMatrix);

			renderer.Draw(entity.GetModel().GetVertexIndexCount());
		}

		{
			glm::mat4 transformationMatrix = entity2.GetTransformationMatrix();

			shader.Bind();
			shader.SetUniformMatrix4f("u_transformationMatrix", transformationMatrix);
			shader.SetUniformMatrix4f("u_viewMatrix", viewMatrix);
			shader.SetUniformMatrix4f("u_projectionMatrix", projectionMatrix);

			renderer.Draw(entity2.GetModel().GetVertexIndexCount());
		}

		displayManager.UpdateDisplay();
	}

	displayManager.~DisplayManager();
	inputManager.~InputManager();

	return 0;
}