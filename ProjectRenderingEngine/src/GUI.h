#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <string>
#include <vector>

enum GUISliderType {
	Float1,
	Float3
};

struct GUISlider {
	std::string Name;
	GUISliderType Type;
	float* Value;
	float MinRange;
	float MaxRange;

	GUISlider(std::string name, GUISliderType type, float* value, float minRange, float maxRange) {
		Name = name;
		Type = type;
		Value = value;
		MinRange = minRange;
		MaxRange = maxRange;
	}
};

class GUI {
private:
	ImGuiContext* m_Context;
	std::vector<GUISlider> m_GUISliders;

public:
	GUI(GLFWwindow* window);
	~GUI() = default;

	void OnGUIUpdate();
	void Cleanup();
	void AddFloat1(std::string name, float* value, float minRange, float maxRange);
	void AddFloat3(std::string name, float* value, float minRange, float maxRange);

	bool LoadModelButtonClicked;
};