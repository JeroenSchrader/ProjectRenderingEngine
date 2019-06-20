#include "DisplayManager.h"
#include <iostream>
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

//For Frame/FpsTimer
double lastTime = glfwGetTime();
int nbFrames = 0;

void OnWindowResize(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

DisplayManager::DisplayManager(unsigned int width, unsigned int height, const char* title)	
{
	InitializeWindow(width, height, title);
}

DisplayManager::~DisplayManager()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void DisplayManager::Prepare() const
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.4f, 0.8f, 1.0f);
}

void DisplayManager::UpdateDisplay()
{
	#pragma region Frame/FpsTimer
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If more than 1 second passed
			// set new window title and reset timer
			char buffer[75];
			sprintf_s(buffer, "%.3f ms/frame | %.2f fps | Rendering Engine by Jeroen Schrader", 1000.0 / double(nbFrames), double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
			SetWindowTitle(buffer);
		}
	#pragma endregion

	/* Swap front and back buffers */
	glfwSwapBuffers(m_Window);
}

void DisplayManager::SetWindowTitle(const char * title)
{
	glfwSetWindowTitle(m_Window, title);
}

bool DisplayManager::ShouldWindowClose()
{
	return glfwWindowShouldClose(m_Window);
}

unsigned int DisplayManager::GetWindowWidth()
{
	int width;
	glfwGetWindowSize(m_Window, &width, NULL);
	return width;
}

unsigned int DisplayManager::GetWindowHeight()
{
	int height;
	glfwGetWindowSize(m_Window, NULL, &height);
	return height;
}

float DisplayManager::GetWindowAspectRatio()
{
	int width, height;
	glfwGetWindowSize(m_Window, &width, &height);
	return (float) width / (float) height;
}

void DisplayManager::InitializeWindow(unsigned int width, unsigned int height, const char* title)
{
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL, use Core profile

	/* Initialize the library */
	if (!glfwInit()) {
		throw std::exception("Initialization of GLFW failed.");
	}

	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!m_Window)
	{
		glfwTerminate();
		throw std::exception("Window creation failed.");
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);
	glfwSetFramebufferSizeCallback(m_Window, OnWindowResize);

	glfwSwapInterval(1);
}
