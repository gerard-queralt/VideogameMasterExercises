#pragma once

#include "Window.h"

#include "glew.h"

class WindowScene : public Window
{
public:
	WindowScene();
	~WindowScene();

	update_status Update();

private:
	GLuint texture;
};

