#pragma once
#include "GLFW/glfw3.h"
#include "GLM/vec2.hpp"

class InputManager {
private:
	GLFWwindow* m_Window;

public:
	InputManager(GLFWwindow* window);
	~InputManager();

	glm::vec2 GetMousePosition();
	void HandleInput();
	bool MouseClicked(int key);
	bool MouseReleased(int key);
	bool KeyPressed(int key);
	bool KeyReleased(int key);
};