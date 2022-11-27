#pragma once

#include "Module.h"

//Time is in milliseconds. Might need to be in seconds
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

	int m_prevTime = 0;
	int m_deltaTime = 0;
};

