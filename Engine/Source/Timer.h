#pragma once

class Timer
{
public:
	void Start();
	int Read();
	int Stop();

private:
	void UpdateDeltaTime();

protected:
	virtual int GetCurrentTime() = 0;

	int m_startTime = 0;
	int m_deltaTime = 0;
	bool m_stopped = false;
};

