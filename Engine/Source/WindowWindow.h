#pragma once

#include "Window.h"

class WindowWindow : public Window
{
public:
	WindowWindow();
	~WindowWindow();

	void Draw();

private:
	bool m_fullscreen = false;
	bool m_resizable = true;
	bool m_borderless = false;
	bool m_fullDesktop = false;
};

