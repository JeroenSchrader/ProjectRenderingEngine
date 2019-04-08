#include <iostream>

#include "Renderer.h"
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

int main() {	
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Rendering Engine by Jeroen Schrader", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Glew init error" << std::endl;
	};

	float vertices[9]{
		-1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	VertexArray vao;
	VertexBuffer vb(vertices, 3 * 3 * sizeof(float));
	VertexBufferLayout layout;

	layout.Push<float>(3);
	vao.AddBuffer(vb, layout);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.4f, 0.8f, 1.0f);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}