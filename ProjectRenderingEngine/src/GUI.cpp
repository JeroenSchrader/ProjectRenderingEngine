#include "GUI.h"

GUI::GUI(GLFWwindow* window)
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
	ImGui::Button("HoiTest");
	for (size_t i = 0; i < m_GUIItems.size(); i++)
	{
		GUIItem item = m_GUIItems[i];
		ImGui::SliderFloat3(item.Name.c_str(), item.Value, item.MinRange, item.MaxRange);
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

void GUI::AddFloat3(std::string name, float* value, float minRange, float maxRange)
{
	m_GUIItems.push_back(GUIItem(name, value, minRange, maxRange));
}
