#include "SubWindow.h"

#include "imgui.h"

bool SubWindow::s_default = true;

SubWindow::SubWindow(const std::string& i_name) : Window(i_name)
{
}

SubWindow::~SubWindow()
{
}

void SubWindow::Draw(bool& i_enabled)
{
	if (ImGui::CollapsingHeader(m_name.c_str())) {
		DrawWindowContents();
	}
}
