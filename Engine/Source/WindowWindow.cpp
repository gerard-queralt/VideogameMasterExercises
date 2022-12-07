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

	bool fullscreen = App->window->IsWindowFullscreen();
	if (ImGui::Checkbox("Fullscreen", &fullscreen)) {
		App->window->SetFullscreen(fullscreen);
	}

	ImGui::SameLine();

	bool resizable = App->window->IsWindowResizable();
	if (ImGui::Checkbox("Resizable", &resizable)) {
		App->window->SetResizable(resizable);
	}
		
	bool borderless = App->window->IsWindowBorderless();
	if (ImGui::Checkbox("Borderless", &borderless)) {
		App->window->SetBorderless(borderless);
	}

	ImGui::SameLine();

	bool fullDesktop = App->window->IsWindowDesktopFullscreen();
	if (ImGui::Checkbox("Desktop Fullscreen", &fullDesktop)) {
		App->window->SetDesktopFullscreen(fullDesktop);
	}
}
