#include "ModuleRenderExercise.h"

#include "Application.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "ModuleWindow.h"
#include "ModuleEditorCamera.h"
#include "ModuleTexture.h"
#include "Model3D.h"
#include "ModuleEditor.h"
#include "MicrosecondTimer.h"

#define VERT_SHADER "default_vertex.glsl"
#define FRAG_SHADER "default_fragment.glsl"

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
	glDeleteBuffers(1, &m_vbo);
	delete m_model3D;
}

bool ModuleRenderExercise::Init()
{
	glEnable(GL_TEXTURE_2D);

	return true;
}

bool ModuleRenderExercise::Start()
{
	m_program = App->program->CreateProgramFromShaders(VERT_SHADER, FRAG_SHADER);

	m_model = float4x4::FromTRS(float3(2.0f, 2.0f, 0.0f),
			float4x4::identity,
			float3(1.0f));

	m_model3D = Model3D::LoadFromFile("BakerHouse.fbx");
	App->editor->SetTargetModel(m_model3D);

	return true;
}

update_status ModuleRenderExercise::Update()
{
	MicrosecondTimer t;
	t.Start();
	m_model3D->Draw();
	LOG_ENGINE(std::to_string(t.Read()).c_str());

	return UPDATE_CONTINUE;
}
