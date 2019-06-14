#pragma once

#include "GLFW/glfw3.h"
#include "GLM/mat4x4.hpp"

class DisplayManager {
private:
	static DisplayManager* m_Instance;
	DisplayManager(unsigned int width, unsigned int height, const char* title);

	GLFWwindow* m_Window;

	void InitializeWindow(unsigned int width, unsigned int height, const char* title);

public:
	static DisplayManager* GetInstance() {
		if (m_Instance) {
			return m_Instance;
		}
		m_Instance = new DisplayManager(1280, 720, "Rendering engine by Jeroen Schrader");
		return m_Instance;
	}

	~DisplayManager();
	void Prepare() const;
	void UpdateDisplay();
	void SetWindowTitle(const char* title);
	bool ShouldWindowClose();

	unsigned int GetWindowWidth();
	unsigned int GetWindowHeight();
	float GetWindowAspectRatio();

	inline GLFWwindow* GetWindow() const { return m_Window; }
};