#include "InputManager.h"

InputManager::InputManager(GLFWwindow * window)
	: m_Window(window)
{

}

InputManager::~InputManager()
{
	glfwTerminate();
}

glm::vec2 InputManager::GetMousePosition()
{
	double mouseX, mouseY;
	glfwGetCursorPos(m_Window, &mouseX, &mouseY);

	return glm::vec2(mouseX, mouseY);
}

void InputManager::HandleInput()
{
	/* Poll for and process events */
	glfwPollEvents();
}

bool InputManager::MouseClicked(int key)
{
	return glfwGetMouseButton(m_Window, key) == GLFW_PRESS;
}

bool InputManager::MouseReleased(int key)
{
	return glfwGetMouseButton(m_Window, key) == GLFW_RELEASE;
}

bool InputManager::KeyPressed(int key)
{
	return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool InputManager::KeyReleased(int key)
{
	return glfwGetKey(m_Window, key) == GLFW_RELEASE;
}
