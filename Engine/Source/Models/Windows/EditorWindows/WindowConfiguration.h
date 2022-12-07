#pragma once

#include "EditorWindow.h"
#include "Models/Windows/SubWindows/SubWindow.h"

#include <list>

class WindowConfiguration : public EditorWindow
{
public:
	WindowConfiguration();
	~WindowConfiguration();

	void DrawWindowContents();

private:
	std::list<SubWindow*> m_collapsingSubWindows;
};

