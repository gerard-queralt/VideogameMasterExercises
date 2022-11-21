#include "WindowConsole.h"

WindowConsole::WindowConsole() : Window("Console")
{
}

WindowConsole::~WindowConsole()
{
}

update_status WindowConsole::Update()
{
	bool enabled;

	if (ImGui::Begin(m_name.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		for (int i = 0; i < m_consloneContents.size(); ++i) {
			const char* line = m_consloneContents[i];
			ImGui::TextUnformatted(line);
		}
	}
	ImGui::End();

	return UPDATE_CONTINUE;
}

void WindowConsole::Output(const char* i_textToPrint)
{
	LOG_ENGINE(i_textToPrint);
	m_consloneContents.push_back(_strdup(i_textToPrint));
}
