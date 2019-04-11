#pragma once

#include "GLFW/glfw3.h"
#include "GLM/mat4x4.hpp"

class DisplayManager {
private:
	GLFWwindow* m_Window;

	void InitializeWindow(unsigned int width, unsigned int height, const char* title);

public:
	DisplayManager(unsigned int width, unsigned int height, const char* title);
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