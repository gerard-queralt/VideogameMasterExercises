#pragma once

#include "Window.h"

class WindowMainMenu : public Window
{
public:
	WindowMainMenu();
	~WindowMainMenu();

	static const std::string s_repositoryLink;

	void Draw();
};

