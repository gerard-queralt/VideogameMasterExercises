#pragma once

#include "Window.h"

#include "imgui.h"

class WindowConsole : public Window
{
public:
	WindowConsole();
	~WindowConsole();

	update_status Update();

	void Output(const char* i_textToPrint);

private:
	ImVector<const char*> m_consloneContents;
};

