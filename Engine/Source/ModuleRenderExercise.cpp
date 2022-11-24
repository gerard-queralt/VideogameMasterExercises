#include "ModuleRenderExercise.h"

#include "Application.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "ModuleWindow.h"
#include "ModuleEditorCamera.h"
#include "ModuleTexture.h"
#include "Model3D.h"

#define VERT_SHADER "default_vertex.glsl"
#define FRAG_SHADER "default_fragment.glsl"

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
	glDeleteBuffers(1, &vbo);
	delete model3D;
}

bool ModuleRenderExercise::Init()
{
	glEnable(GL_TEXTURE_2D);

	return true;
}

bool ModuleRenderExercise::Start()
{
	program = App->program->CreateProgramFromShaders(VERT_SHADER, FRAG_SHADER);

	model = float4x4::FromTRS(float3(2.0f, 2.0f, 0.0f),
			float4x4::identity,
			float3(1.0f));

	model3D = new Model3D();
	model3D->LoadFromFile("BakerHouse.fbx");

	return true;
}

update_status ModuleRenderExercise::Update()
{
	model3D->Draw();

	return UPDATE_CONTINUE;
}
