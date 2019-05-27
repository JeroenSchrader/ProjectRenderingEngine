#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class GUI {
private:
	ImGuiContext* m_Context;

public:
	GUI(GLFWwindow* window);
	~GUI() = default;

	void OnGUIUpdate();
	void Cleanup();
};