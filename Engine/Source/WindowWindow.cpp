#include "WindowWindow.h"

#include "imgui.h"

#include "Application.h"
#include "ModuleWindow.h"

WindowWindow::WindowWindow() : Window("Window")
{
}

WindowWindow::~WindowWindow()
{
}

update_status WindowWindow::Update()
{
	bool enabled;

	if (ImGui::CollapsingHeader(m_name.c_str())) {
		if (ImGui::Checkbox("Fullscreen", &m_fullscreen)) {
			App->window->SetFullscreen(m_fullscreen);
			if (m_fullscreen) {
				m_resizable = m_borderless = m_fullDesktop = false;
			}
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &m_resizable)) {
			App->window->SetResizable(m_resizable);
			if (m_resizable) {
				m_borderless = m_fullDesktop = m_fullscreen = false;
			}
		}
		
		if (ImGui::Checkbox("Borderless", &m_borderless)) {
			App->window->SetBorderless(m_borderless);
			if (m_borderless) {
				m_fullDesktop = m_fullscreen = m_resizable = false;
			}
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Desktop Fullscreen", &m_fullDesktop)) {
			App->window->SetDesktopFullscreen(m_fullDesktop);
			if (m_fullDesktop) {
				m_fullscreen = m_resizable = m_borderless = false;
			}
		}
	}

	return UPDATE_CONTINUE;
}
