#include "WindowMainMenu.h"

#include "imgui.h"
#include "SDL.h"

const std::string WindowMainMenu::s_repositoryLink = "https://github.com/gerard-queralt/VideogameMasterExercises/tree/main/Engine";
bool WindowMainMenu::s_default = true;

WindowMainMenu::WindowMainMenu() : Window("Main Menu")
{
}

WindowMainMenu::~WindowMainMenu()
{
}

void WindowMainMenu::SetUpWindowsMenu(std::list<EditorWindow*>& i_windows)
{
	for (std::list<EditorWindow*>::iterator it = i_windows.begin(); it != i_windows.end(); ++it) {
		m_windowNames.push_back((*it)->GetName());
		m_windowsEnabled.push_back(true);
	}
}

void WindowMainMenu::Draw(bool& i_enabled)
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::MenuItem("GitHub Link")) {
			ShellExecute(NULL, "open", s_repositoryLink.c_str(), NULL, NULL, SW_SHOWNORMAL);
		}
		if (ImGui::MenuItem("Exit")) {
			//to make it easier in terms of coupling between classes,
			//just push an SDL_QuitEvent to the event queue
			SDL_Event quitEvent;
			quitEvent.type = SDL_QUIT;
			SDL_PushEvent(&quitEvent);
		}
	}
	ImGui::EndMainMenuBar();
}
