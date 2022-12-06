#include "EditorWindow.h"

EditorWindow::EditorWindow(const std::string& i_name) : Window(i_name)
{
}

EditorWindow::~EditorWindow()
{
}

void EditorWindow::Draw(bool& io_enabled)
{
	if (ImGui::Begin(m_name.c_str(), &io_enabled, m_flags)) {
		DrawWindowContents();
		m_focused = ImGui::IsWindowFocused();
	}
	else {
		m_focused = false;
	}
	ImGui::End();
}
