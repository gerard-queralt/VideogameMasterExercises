#pragma once

#include "Module.h"

#include <list>
#include "Window.h"
#include "WindowConsole.h"

class ModuleEditor : public Module
{
public:
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void OutputToConsole(const char* i_textToPrint);

private:
	std::list<Window*> m_windows;
	WindowConsole* m_console = nullptr;
};

