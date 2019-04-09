#include <iostream>

#include "Renderer.h"
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

int main() {	
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL, use Core profile

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

	//Rectangle vertices
	float vertices[]{
		-0.8f, -0.8f, 0.0f,	//lower left
		-0.8f,  0.8f, 0.0f, //upper left
		 0.8f,  0.8f, 0.0f,	//upper right
		 0.8f, -0.8f, 0.0f	//lower right
	};

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer vb(vertices, 4 * 3 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(3);

	IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

	VertexArray vao;
	vao.AddBuffer(vb, layout);

	Shader shader("src/Shaders/BasicShader.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.9, 0.2, 0.2, 1.0);

	//For Frame/FpsTimer
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	
	/* Loop until the user closes the window or presses the Escape key */
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window))
	{
		#pragma region Frame/FpsTimer
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
			// set new window title and reset timer
			char buffer[75];
			sprintf_s(buffer, "%.3f ms/frame | %.2f fps | Rendering Engine by Jeroen Schrader", 1000.0 / double(nbFrames), double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
			glfwSetWindowTitle(window, buffer);
		}
		#pragma endregion
			   
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.4f, 0.8f, 1.0f);
		
		ib.Bind();
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.9, 0.2, 0.2, 1.0);

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}