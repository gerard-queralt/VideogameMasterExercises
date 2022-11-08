#include "ModuleRenderExercise.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "ModuleWindow.h"

#define VERT_SHADER "default_vertex.glsl"
#define FRAG_SHADER "default_fragment.glsl"

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
	glDeleteBuffers(1, &vbo);
}

bool ModuleRenderExercise::Init()
{
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	return true;
}

bool ModuleRenderExercise::Start()
{
	program = App->program->CreateProgramFromShaders(VERT_SHADER, FRAG_SHADER);

	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);
	
	frustum.SetPos(float3(0.0f, 3.0f, 5.0f));
	frustum.SetFront(-float3::unitZ);
	frustum.SetUp(float3::unitY);
	
	frustum.SetViewPlaneDistances(0.1f, 100.0f);

	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	frustum.SetHorizontalFovAndAspectRatio((math::pi / 180.0f) * 90.0f, ((float)w) / ((float)h));
	
	proj = frustum.ProjectionMatrix();
	model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f));
	view = frustum.ViewMatrix();

	return true;
}

update_status ModuleRenderExercise::Update()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glUseProgram(program);

	glUniformMatrix4fv(0, 1, GL_TRUE, &proj[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	return UPDATE_CONTINUE;
}
