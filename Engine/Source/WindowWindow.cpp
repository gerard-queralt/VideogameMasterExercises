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

void WindowWindow::Draw()
{
	if (ImGui::CollapsingHeader(m_name.c_str())) {
		bool widthChanged = ImGui::SliderInt("Window Width", &m_windowWidth, 640, 1920, "%d", ImGuiSliderFlags_AlwaysClamp);
		bool heighChanged = ImGui::SliderInt("Window Height", &m_windowHeight, 360, 1080, "%d", ImGuiSliderFlags_AlwaysClamp);
		if (widthChanged || heighChanged)
			App->window->ResizeWindow(m_windowWidth, m_windowHeight);

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
}
