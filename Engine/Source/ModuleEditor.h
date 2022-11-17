#pragma once

#include "Module.h"

#include "imgui.h"

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
	update_status UpdateConsole();

	ImVector<const char*> consloneContents;
};

