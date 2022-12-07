#include "Timer.h"

void Timer::Start()
{
    m_stopped = false;
    m_startTime = GetCurrentTime();
    m_deltaTime = 0;
}

int Timer::Read()
{
    if (!m_stopped) {
        UpdateDeltaTime();
    }
    return m_deltaTime;
}

int Timer::Stop()
{
    UpdateDeltaTime();
    m_stopped = true;
    return Read();
}

void Timer::UpdateDeltaTime()
{
    m_deltaTime = GetCurrentTime() - m_startTime;
}
