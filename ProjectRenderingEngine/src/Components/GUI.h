#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <string>
#include <vector>

class Scene;
class Entity;

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

	void AddFloat1(std::string name, float* value, float minRange, float maxRange);
	void AddFloat3(std::string name, float* value, float minRange, float maxRange);

public:
	GUI(GLFWwindow* window);
	~GUI() = default;

	void InitializeSceneGUI(Scene* scene);
	void AddEntityToGUI(Entity* entity);

	void OnGUIUpdate();
	void Cleanup();

	bool LoadModelButtonClicked;
	bool LoadNextSceneButtonClicked;
	bool GreyScaleEffectEnabled;
	bool InverseColorEffectEnabled;
};