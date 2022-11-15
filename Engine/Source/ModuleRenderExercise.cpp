#include "ModuleRenderExercise.h"

#include "Application.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "ModuleWindow.h"
#include "ModuleEditorCamera.h"
#include "ModuleTexture.h"

#define VERT_SHADER "default_vertex.glsl"
#define FRAG_SHADER "default_fragment.glsl"
#define TEXTURE "tex.png"

#define NUM_VERTEX 4
#define NUM_TRIANGLE math::Ceil(NUM_VERTEX / 3.0f) //num vertex divided by vertex per triangle, rounded up

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
	glDeleteBuffers(1, &vbo);
	glDeleteTextures(1, &texture);
}

bool ModuleRenderExercise::Init()
{
	float vtx_data[] = { 
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	glEnable(GL_TEXTURE_2D);

	return true;
}

bool ModuleRenderExercise::Start()
{
	program = App->program->CreateProgramFromShaders(VERT_SHADER, FRAG_SHADER);

	model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
			float4x4::RotateZ(pi / 4.0f),
			float3(2.0f, 1.0f, 0.0f));

	//load texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	DirectX::ScratchImage imageTexture = App->texture->LoadTextureFromFile(TEXTURE);

	GLint width, height, internalFormat, format, type;
	App->texture->LoadInformationFromImage(imageTexture, width, height, internalFormat, format, type);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, imageTexture.GetPixels());

	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}

update_status ModuleRenderExercise::Update()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * NUM_VERTEX) /*buffer offset*/);

	glUseProgram(program);

	glUniformMatrix4fv(0, 1, GL_TRUE, &App->camera->getProj()[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &App->camera->getView()[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &getModel()[0][0]);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3 * NUM_TRIANGLE);

	return UPDATE_CONTINUE;
}
