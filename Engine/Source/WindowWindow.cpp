#include "WindowWindow.h"

#include "imgui.h"

#include "Application.h"
#include "ModuleWindow.h"

WindowWindow::WindowWindow() : SubWindow("Window")
{
}

WindowWindow::~WindowWindow()
{
}

void WindowWindow::DrawWindowContents()
{
	int width, height;
	SDL_GetWindowSize(App->window->m_window, &width, &height);
	bool widthChanged = ImGui::SliderInt("Window Width", &width, 640, 1920, "%d", ImGuiSliderFlags_AlwaysClamp);
	bool heighChanged = ImGui::SliderInt("Window Height", &height, 360, 1080, "%d", ImGuiSliderFlags_AlwaysClamp);
	if (widthChanged || heighChanged)
		App->window->ResizeWindow(width, height);

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
