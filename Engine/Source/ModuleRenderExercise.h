#pragma once

#include "Module.h"
#include <glew.h>

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	bool Start();
	update_status Update();

private:
	GLuint vbo;
	GLuint program;
};

