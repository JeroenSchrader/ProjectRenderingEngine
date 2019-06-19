#include "GUI.h"

#include "LightingInformation.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Entity.h"

#include <map>
#include <string>

const float MaxEntityPosition = 15.0f;
const float MaxEntityRotation = 360.0f;
const float MaxRGBColorRange = 1.0f;

GUI::GUI(GLFWwindow* window)
	: LoadModelButtonClicked(false), LoadNextSceneButtonClicked(false)
{
	m_Context = ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");	
}

void GUI::InitializeSceneGUI(Scene* scene)
{
	m_GUISliders.clear();

	LightingInformation* lightInformation = scene->m_LightInformation;

	AddFloat3("Ambient Light Color", &lightInformation->AmbientColor.x, 0, MaxRGBColorRange);
	AddFloat1("Ambient Light Strength", &lightInformation->AmbientStrength, 0, MaxRGBColorRange);
	AddFloat3("Diffuse Light Color", &lightInformation->DiffuseColor.x, 0, MaxRGBColorRange);
	AddFloat1("Diffuse Light Strength", &lightInformation->DiffuseStrength, 0, MaxRGBColorRange);
	AddFloat3("Specular Light Color", &lightInformation->SpecularColor.x, 0, MaxRGBColorRange);
	AddFloat1("Specular Light Strength", &lightInformation->SpecularStrength, 0, MaxRGBColorRange);

	ResourceManager* resourceManager = ResourceManager::GetInstance();

	std::map<std::string, Entity*> entities = resourceManager->GetEntities();
	for (std::map<std::string, Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		//Add all GUI items for each entity in the world
		AddFloat3(it->first, &it->second->GetPosition().x, -MaxEntityPosition, MaxEntityPosition);
		AddFloat3(it->first + " Rotation", &it->second->GetRotation().x, 0, MaxEntityRotation);
	}
}

void GUI::AddEntityToGUI(Entity* entity)
{
	AddFloat3(entity->GetName(), &entity->GetPosition().x, -MaxEntityPosition, MaxEntityPosition);
	AddFloat3(entity->GetName() + " Rotation", &entity->GetRotation().x, 0, MaxEntityRotation);
}

void GUI::OnGUIUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Controls");
	if (ImGui::Button("Load Model")) {
		LoadModelButtonClicked = true;
	}
	if (ImGui::ArrowButton("Arrow_Right", ImGuiDir_Right)) {
		LoadNextSceneButtonClicked = true;
	}

	for (size_t i = 0; i < m_GUISliders.size(); i++)
	{
		GUISlider item = m_GUISliders[i];
		switch (item.Type) {
			case GUISliderType::Float1:
				ImGui::SliderFloat(item.Name.c_str(), item.Value, item.MinRange, item.MaxRange);
				break;
			case GUISliderType::Float3:
				ImGui::SliderFloat3(item.Name.c_str(), item.Value, item.MinRange, item.MaxRange);
				break;
		}
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext(m_Context);

}

void GUI::AddFloat1(std::string name, float* value, float minRange, float maxRange) {
	m_GUISliders.push_back(GUISlider(name, GUISliderType::Float1, value, minRange, maxRange));
}

void GUI::AddFloat3(std::string name, float* value, float minRange, float maxRange)
{
	m_GUISliders.push_back(GUISlider(name, GUISliderType::Float3, value, minRange, maxRange));
}


