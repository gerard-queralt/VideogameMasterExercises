#pragma once

#include "Window.h"

#include <list>

class WindowConfiguration : public Window
{
public:
	WindowConfiguration();
	~WindowConfiguration();

	void Draw();

private:
	std::list<Window*> m_collapsingSubWindows;
};

