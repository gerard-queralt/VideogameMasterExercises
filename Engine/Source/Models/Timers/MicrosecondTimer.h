#pragma once

#include "Timer.h"

#include "SDL.h"

class MicrosecondTimer : public Timer
{
public:
	MicrosecondTimer();
	~MicrosecondTimer();

protected:
	int GetCurrentTime();

private:
	static Uint64 PerformanceFrequency;
};

