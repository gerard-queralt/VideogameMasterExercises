#include "WindowWindow.h"

#include "imgui.h"

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
		bool fullscreen;
		if (ImGui::Checkbox("Fullscreen", &fullscreen));
	}

	return UPDATE_CONTINUE;
}
