#include "WindowConfiguration.h"

#include "imgui.h"

#include "WindowFPS.h"
#include "WindowWindow.h"
#include "WindowInput.h"

WindowConfiguration::WindowConfiguration() : Window("Configuration")
{
	m_collapsingSubWindows.push_back(new WindowFPS());
	m_collapsingSubWindows.push_back(new WindowWindow());
	m_collapsingSubWindows.push_back(new WindowInput());
}

WindowConfiguration::~WindowConfiguration()
{
	for (Window* window : m_collapsingSubWindows)
		delete window;
	m_collapsingSubWindows.clear();
}

void WindowConfiguration::Draw()
{
	bool enabled;

	if (ImGui::Begin(m_name.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		for (std::list<Window*>::iterator it = m_collapsingSubWindows.begin(); it != m_collapsingSubWindows.end(); ++it)
			(*it)->Draw();
	}
	ImGui::End();
}
