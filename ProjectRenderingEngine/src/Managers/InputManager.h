#pragma once
#include "GLFW/glfw3.h"
#include "GLM/vec2.hpp"
#include "DisplayManager.h"

class InputManager {
private:
	static InputManager* m_Instance;
	InputManager(GLFWwindow* window);

	GLFWwindow* m_Window;
	GLFWscrollfun* m_ScrollCallback;

public:
	static InputManager* GetInstance() {
		if (m_Instance) {
			return m_Instance;
		}
		m_Instance = new InputManager(DisplayManager::GetInstance()->GetWindow());
		return m_Instance;
	}

	~InputManager();

	glm::vec2 GetMousePosition();
	void HandleInput();
	bool MouseClicked(int key);
	bool MouseReleased(int key);
	bool KeyPressed(int key);
	bool KeyReleased(int key);
};