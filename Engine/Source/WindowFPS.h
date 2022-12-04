#pragma once

#include "Window.h"

#include <vector>

class WindowFPS : public Window
{
public:
	WindowFPS();
	~WindowFPS();

	void Draw();

private:
	int m_fpsCaptures = 100;
	int m_currentIndex = 0;
	std::vector<float> m_fpsHist;
};

