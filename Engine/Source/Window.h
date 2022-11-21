#pragma once

#include "Globals.h"
#include <string>

class Window
{
public:
	Window(std::string i_name);
	~Window();

	virtual update_status Update();
protected:
	std::string m_name;
};

