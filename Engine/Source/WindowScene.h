#pragma once

#include "EditorWindow.h"

#include "glew.h"

class WindowScene : public EditorWindow
{
public:
	WindowScene();
	~WindowScene();

	void DrawWindowContents();

private:
	void ManageResize();

	GLuint texture = 0;
	float m_previousWidht = 0;
	float m_previousHeight = 0;
};

