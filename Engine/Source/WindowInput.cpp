#include "WindowInput.h"

#include "imgui.h"

#include "Application.h"
#include "ModuleInput.h"

WindowInput::WindowInput() : Window("Input")
{
}

WindowInput::~WindowInput()
{
}

update_status WindowInput::Update()
{
	if (ImGui::CollapsingHeader(m_name.c_str())) {
		ImGui::SliderFloat("Camera speed", &App->input->m_cameraSpeed, 0.01f, 0.1f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
		ImGui::SliderFloat("Rotation speed", &App->input->m_angleSpeed, 0.001f, 0.01f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
	}

	return UPDATE_CONTINUE;
}
