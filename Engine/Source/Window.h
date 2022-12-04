#pragma once

#include "Globals.h"
#include <string>

class Window
{
public:
	~Window() {}

	virtual void Draw() = 0;
	
protected:
	Window(const std::string& i_name) {
		m_name = i_name;
	}

	std::string m_name;
};

