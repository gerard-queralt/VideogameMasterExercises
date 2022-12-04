#pragma once

#include "Window.h"

class WindowInput : public Window
{
public:
	WindowInput();
	~WindowInput();

	update_status Update();
};

