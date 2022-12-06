#include "WindowConsole.h"

WindowConsole::WindowConsole() : EditorWindow("Console")
{
	m_flags |= ImGuiWindowFlags_AlwaysAutoResize;
}

WindowConsole::~WindowConsole()
{
}

void WindowConsole::DrawWindowContents()
{
	for (int i = 0; i < m_consloneContents.size(); ++i) {
		const char* line = m_consloneContents[i];
		ImGui::TextUnformatted(line);
	}
}

void WindowConsole::Output(const char* i_textToPrint)
{
	LOG_ENGINE(i_textToPrint);
	m_consloneContents.push_back(_strdup(i_textToPrint));
}
