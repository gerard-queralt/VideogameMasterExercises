#pragma once

#include "Window.h"

class WindowFPS : public Window
{
public:
	WindowFPS();
	~WindowFPS();

	update_status Update();
};

