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
	glDeleteProgram(m_program);
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

	SetModel3D((Model3D::s_modelFolderPath + "BakerHouse.fbx").c_str());

	return true;
}

update_status ModuleRenderExercise::Update()
{
	if (m_model3D != nullptr)
		m_model3D->Draw();

	return UPDATE_CONTINUE;
}

void ModuleRenderExercise::SetModel3D(const char* i_modelPath)
{
	delete m_model3D;
	m_model3D = Model3D::LoadFromFile(i_modelPath);
	App->editor->SetTargetModel(m_model3D);
}
