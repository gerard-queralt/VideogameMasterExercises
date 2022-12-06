#pragma once

#include "Window.h"

#include <list>
#include <vector>

#include "EditorWindow.h"

class WindowMainMenu : public Window
{
public:
	WindowMainMenu();
	~WindowMainMenu();

	static const std::string s_repositoryLink;

	void SetUpWindowsMenu(std::list<EditorWindow*>& i_windows);

	void Draw(bool& i_enabled = s_default);

	bool IsWindowEnabled(int i_windowIndex) {
		return m_windowsEnabled[i_windowIndex];
	}
	void SetWindowEnabled(int i_windowIndex, bool i_enabled) {
		m_windowsEnabled[i_windowIndex] = i_enabled;
	}

private:
	static bool s_default;

	std::vector<std::string> m_windowNames;
	std::vector<bool> m_windowsEnabled;
};

