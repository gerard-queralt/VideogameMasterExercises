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

	float4x4 GetModel() {
		return m_model;
	}

	GLuint GetProgram() {
		return m_program;
	}

	void SetModel3D(const char* i_modelPath);

private:
	GLuint m_program;
	Model3D* m_model3D;
	float4x4 m_model;
};

