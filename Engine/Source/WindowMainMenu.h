#pragma once

#include "Window.h"

#include <list>
#include <vector>

#include "EditorWindow.h"

class WindowMainMenu : public Window
{
public:
	WindowMainMenu(std::list<EditorWindow*>& i_editorWindows);
	~WindowMainMenu();

	static const std::string s_repositoryLink;

	void Draw(bool& i_enabled = s_default);

	bool IsWindowEnabled(int i_windowIndex) {
		return m_windowsEnabled[i_windowIndex];
	}
	void SetWindowEnabled(int i_windowIndex, bool i_enabled) {
		m_windowsEnabled[i_windowIndex] = i_enabled;
	}

private:
	void DrawWindowsMenu();
	void DrawGithubLink();
	void DrawExit();

	static bool s_default;

	int m_nWindows;
	std::vector<std::string> m_windowNames;
	std::vector<bool> m_windowsEnabled;
};

