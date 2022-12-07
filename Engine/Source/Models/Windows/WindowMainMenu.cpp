#include "WindowMainMenu.h"

#include "imgui.h"
#include "SDL.h"

const std::string WindowMainMenu::s_repositoryLink = "https://github.com/gerard-queralt/VideogameMasterExercises/tree/main/Engine";
bool WindowMainMenu::s_default = true;

WindowMainMenu::WindowMainMenu(std::list<EditorWindow*>& i_editorWindows) : Window("Main Menu")
{
	m_nWindows = i_editorWindows.size();
	for (std::list<EditorWindow*>::iterator it = i_editorWindows.begin(); it != i_editorWindows.end(); ++it) {
		m_windowNames.push_back((*it)->GetName());
		m_windowsEnabled.push_back(true);
	}
}

WindowMainMenu::~WindowMainMenu()
{
}

void WindowMainMenu::Draw(bool& i_enabled)
{
	if (ImGui::BeginMainMenuBar()) {
		DrawWindowsMenu();
		DrawGithubLink();
		DrawExit();
	}
	ImGui::EndMainMenuBar();
}

void WindowMainMenu::DrawWindowsMenu()
{
	if (ImGui::BeginMenu("Windows")) {
		for (int i = 0; i < m_nWindows; ++i) {
			bool windowEnabled = IsWindowEnabled(i);
			ImGui::MenuItem(m_windowNames[i].c_str(), NULL, &windowEnabled);
			SetWindowEnabled(i, windowEnabled);
		}
		ImGui::EndMenu();
	}
}

void WindowMainMenu::DrawGithubLink()
{
	if (ImGui::MenuItem("GitHub Link")) {
		ShellExecute(NULL, "open", s_repositoryLink.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}
}

void WindowMainMenu::DrawExit()
{
	if (ImGui::MenuItem("Exit")) {
		//to make it easier in terms of coupling between classes,
		//just push an SDL_QuitEvent to the event queue
		SDL_Event quitEvent;
		quitEvent.type = SDL_QUIT;
		SDL_PushEvent(&quitEvent);
	}
}
