#pragma once
#include "Module.h"
#include "Globals.h"

#include "glew.h"
#include "float4x4.h"

#include "Model3D.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned i_width, unsigned i_height);

	float4x4 GetModel() {
		return m_model;
	}
	GLuint GetProgram() {
		return m_program;
	}
	void SetModel3D(const char* i_modelPath);

	GLuint m_framebuffer = 0;
	GLuint m_renderedTexture = 0;

private:
	friend class ModuleEditor;

	void* m_context;

	GLuint m_depthrenderbuffer;
	GLuint m_program;
	Model3D* m_model3D;
	float4x4 m_model;
	const char* m_vertexShader = "default_vertex.glsl";
	const char* m_fragmentShader = "default_fragment.glsl";
};
