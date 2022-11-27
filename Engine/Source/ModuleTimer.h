#pragma once

#include "Module.h"

class ModuleTimer : public Module
{
public:
	ModuleTimer();
	~ModuleTimer();

	bool Start();
	update_status PreUpdate();

	int GetDeltaTime() {
		return m_deltaTime;
	}

private:
	int GetCurrentSDLTime();

	int m_prevTime;
	int m_deltaTime;
};

