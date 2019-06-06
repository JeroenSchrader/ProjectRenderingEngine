#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <string>
#include <vector>

struct GUIItem {
	std::string Name;
	float* Value;
	float MinRange;
	float MaxRange;

	GUIItem(std::string name, float* value, float minRange, float maxRange) {
		Name = name;
		Value = value;
		MinRange = minRange;
		MaxRange = maxRange;
	}
};

class GUI {
private:
	ImGuiContext* m_Context;
	std::vector<GUIItem> m_GUIItems;

public:
	GUI(GLFWwindow* window);
	~GUI() = default;

	void OnGUIUpdate();
	void Cleanup();
	void AddFloat3(std::string name, float* value, float minRange, float maxRange);
};