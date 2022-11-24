#pragma once

#include "Module.h"

#include <glew.h>

#include "float4x4.h"

#include "Model3D.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	bool Start();
	update_status Update();

	float4x4 getModel() {
		return model;
	}

	GLuint getProgram() {
		return program;
	}

private:
	GLuint vbo;
	GLuint program;
	Model3D* model3D;
	float4x4 model;
};

