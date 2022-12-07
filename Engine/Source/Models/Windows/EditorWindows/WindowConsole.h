#pragma once

#include "EditorWindow.h"

class WindowConsole : public EditorWindow
{
public:
	WindowConsole();
	~WindowConsole();

	void DrawWindowContents();

	void Output(const char* i_textToPrint);

private:
	ImVector<const char*> m_consloneContents;
};

