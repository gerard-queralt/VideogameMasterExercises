#pragma once

#include "Window.h"

class WindowWindow : public Window
{
public:
	WindowWindow();
	~WindowWindow();

	update_status Update();

private:
	bool m_fullscreen = false;
	bool m_resizable = true;
	bool m_borderless = false;
	bool m_fullDesktop = false;
};

