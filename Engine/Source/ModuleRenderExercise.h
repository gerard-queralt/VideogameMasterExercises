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

	float4x4 getProj() {
		return proj;
	}
	float4x4 getModel() {
		return model;
	}
	float4x4 getView() {
		return view;
	}

private:
	GLuint vbo;
	GLuint program;
	Frustum frustum;
	float4x4 proj;
	float4x4 model;
	float4x4 view;
};

