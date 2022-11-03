#pragma once

#include "Module.h"

class ModuleEditor : public Module
{
public:
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

