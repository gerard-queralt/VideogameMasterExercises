#pragma once

#include "SubWindow.h"

#include <string>

class WindowRenderer : public SubWindow
{
public:
	WindowRenderer();
	~WindowRenderer();

	void DrawWindowContents();

private:
	static int s_bufferSize;

	std::string m_vertexShaderBuffer;
	std::string m_fragmentShaderBuffer;
};

