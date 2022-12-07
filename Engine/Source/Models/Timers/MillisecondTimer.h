#pragma once

#include "Timer.h"

class MillisecondTimer : public Timer
{
public:
	MillisecondTimer();
	~MillisecondTimer();

protected:
	int GetCurrentTime();
};

