#include "WindowConfiguration.h"

#include "WindowFPS.h"
#include "WindowWindow.h"
#include "WindowInput.h"

WindowConfiguration::WindowConfiguration() : EditorWindow("Configuration")
{
	m_flags |= ImGuiWindowFlags_AlwaysAutoResize;

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

void WindowConfiguration::DrawWindowContents()
{
	for (std::list<SubWindow*>::iterator it = m_collapsingSubWindows.begin(); it != m_collapsingSubWindows.end(); ++it)
		(*it)->Draw();
}
