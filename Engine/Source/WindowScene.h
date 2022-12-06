#pragma once

#include "Window.h"

#include "glew.h"

class WindowScene : public Window
{
public:
	WindowScene();
	~WindowScene();

	void Draw();

private:
	void ManageResize();

	GLuint texture;
	float m_previousWidht;
	float m_previousHeight;
};

