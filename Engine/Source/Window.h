#pragma once

#include "Globals.h"
#include <string>

class Window
{
public:
	~Window();

	virtual void Start();
	virtual update_status Update();
protected:
	Window(const std::string& i_name);

	std::string m_name;
};

