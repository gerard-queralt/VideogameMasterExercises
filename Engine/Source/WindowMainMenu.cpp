#include "WindowMainMenu.h"

#include "imgui.h"
#include "SDL.h"

const std::string WindowMainMenu::s_repositoryLink = "https://github.com/gerard-queralt/VideogameMasterExercises/tree/main/Engine";

WindowMainMenu::WindowMainMenu() : Window("Main Menu")
{
}

WindowMainMenu::~WindowMainMenu()
{
}

void WindowMainMenu::Draw()
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
