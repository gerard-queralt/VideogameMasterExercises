#pragma once

#include "Module.h"
#include <glew.h>
#include "Frustum.h"

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
	Frustum frustum;
	float4x4 proj;
	float4x4 model;
	float4x4 view;
};

