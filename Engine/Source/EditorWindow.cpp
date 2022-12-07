#include "EditorWindow.h"

EditorWindow::EditorWindow(const std::string& i_name) : Window(i_name)
{
}

EditorWindow::~EditorWindow()
{
}

void EditorWindow::Draw(bool& io_enabled)
{
	if (io_enabled) {
		if (ImGui::Begin(m_name.c_str(), &io_enabled, m_flags)) {
			DrawWindowContents();
			m_focused = ImGui::IsWindowFocused();
		}
		ImGui::End();
	}
	//The call to ImGui::Begin can change the value of io_enabled
	//so using "else" will cause the window to remain focused for an extra frame
	if (!io_enabled) {
		m_focused = false;
	}
}
