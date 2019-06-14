#include "GUI.h"

GUI::GUI(GLFWwindow* window)
	: LoadModelButtonClicked(false)
{
	m_Context = ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");	
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


