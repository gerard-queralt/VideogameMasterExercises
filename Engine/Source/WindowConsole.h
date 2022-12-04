#pragma once

#include "Window.h"

#include "imgui.h"

class WindowConsole : public Window
{
public:
	WindowConsole();
	~WindowConsole();

	void Draw();

	void Output(const char* i_textToPrint);

private:
	ImVector<const char*> m_consloneContents;
};

