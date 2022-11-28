#include "MicrosecondTimer.h"

Uint64 MicrosecondTimer::PerformanceFrequency = SDL_GetPerformanceFrequency();

MicrosecondTimer::MicrosecondTimer()
{
}

MicrosecondTimer::~MicrosecondTimer()
{
}

int MicrosecondTimer::GetCurrentTime()
{
	return SDL_GetPerformanceCounter() * PerformanceFrequency;
}
