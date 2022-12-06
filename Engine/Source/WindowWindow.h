#pragma once

#include "SubWindow.h"

class WindowWindow : public SubWindow
{
public:
	WindowWindow();
	~WindowWindow();

	void DrawWindowContents();

private:
	bool m_fullscreen = false;
	bool m_resizable = true;
	bool m_borderless = false;
	bool m_fullDesktop = false;
};

