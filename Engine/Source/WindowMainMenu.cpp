#include "WindowMainMenu.h"

#include "imgui.h"
#include "SDL.h"

WindowMainMenu::WindowMainMenu() : Window("Main Menu")
{
}

WindowMainMenu::~WindowMainMenu()
{
}

void WindowMainMenu::Draw()
{
	if (ImGui::BeginMainMenuBar()) {
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
