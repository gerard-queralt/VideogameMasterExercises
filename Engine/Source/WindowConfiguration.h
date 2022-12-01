#pragma once

#include "Window.h"

#include <list>

class WindowConfiguration : public Window
{
public:
	WindowConfiguration();
	~WindowConfiguration();

	update_status Update();

private:
	std::list<Window*> m_collapsingSubWindows;
};

