#include "MillisecondTimer.h"

#include "SDL.h"

MillisecondTimer::MillisecondTimer()
{
}

MillisecondTimer::~MillisecondTimer()
{
}

int MillisecondTimer::GetCurrentTime()
{
	return SDL_GetTicks();
}
