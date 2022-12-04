#pragma once

#include "Window.h"

class WindowWindow : public Window
{
public:
	WindowWindow();
	~WindowWindow();

	void Draw();

private:
	int m_windowWidth = SCREEN_WIDTH;
	int m_windowHeight = SCREEN_HEIGHT;
	bool m_fullscreen = false;
	bool m_resizable = true;
	bool m_borderless = false;
	bool m_fullDesktop = false;
};

