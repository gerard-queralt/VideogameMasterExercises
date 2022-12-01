#pragma once

#include "Window.h"

class WindowWindow : public Window
{
public:
	WindowWindow();
	~WindowWindow();

	update_status Update();
};

