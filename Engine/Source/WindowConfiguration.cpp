#include "WindowConfiguration.h"

#include "imgui.h"

#include "WindowFPS.h"
#include "WindowWindow.h"

WindowConfiguration::WindowConfiguration() : Window("Configuration")
{
	m_collapsingSubWindows.push_back(new WindowFPS());
	m_collapsingSubWindows.push_back(new WindowWindow());
}

WindowConfiguration::~WindowConfiguration()
{
	for (Window* window : m_collapsingSubWindows)
		delete window;
	m_collapsingSubWindows.clear();
}

update_status WindowConfiguration::Update()
{
	bool enabled;
	update_status res = UPDATE_CONTINUE;

	if (ImGui::Begin(m_name.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		for (std::list<Window*>::iterator it = m_collapsingSubWindows.begin();
			res == UPDATE_CONTINUE && it != m_collapsingSubWindows.end();
			++it) {
			res = (*it)->Update();
		}
	}
	ImGui::End();

	return res;
}
