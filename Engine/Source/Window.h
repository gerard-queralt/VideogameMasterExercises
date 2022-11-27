#pragma once

#include "Globals.h"
#include <string>

class Window
{
public:
	~Window();

	virtual update_status Update();
protected:
	Window(std::string i_name);

	std::string m_name;
};

