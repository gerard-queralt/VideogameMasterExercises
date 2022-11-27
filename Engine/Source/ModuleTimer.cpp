#include "ModuleTimer.h"

#include "SDL.h"

ModuleTimer::ModuleTimer()
{
}

ModuleTimer::~ModuleTimer()
{
}

bool ModuleTimer::Start()
{
	m_prevTime = GetCurrentSDLTime();

	return true;
}

update_status ModuleTimer::PreUpdate()
{
	int currentTime = GetCurrentSDLTime();
	m_deltaTime = currentTime - m_prevTime;
	m_prevTime = currentTime;

	return UPDATE_CONTINUE;
}

int ModuleTimer::GetCurrentSDLTime()
{
	//SDL_GetTicks returns milliseconds
	return SDL_GetTicks() / 1000;
}
