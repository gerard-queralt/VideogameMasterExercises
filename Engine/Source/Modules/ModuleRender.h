#pragma once
#include "Module.h"
#include "Globals.h"

#include "glew.h"
#include "Math/float4x4.h"

#include "Models/3DModels/Model3D.h"

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

	void UpdateBuffers(unsigned i_width, unsigned i_height);
	void SetModel3D(const char* i_modelPath);
	void FocusCameraOnModel();
	void SetShaders(const char* i_vertexShader, const char* i_fragmentShader);

	float4x4 GetModel() {
		return m_model;
	}
	GLuint GetProgram() {
		return m_program;
	}
	const char* GetVertexShader() {
		return m_vertexShader;
	}
	const char* GetFragmentShader() {
		return m_fragmentShader;
	}

	GLuint m_framebuffer = 0;
	GLuint m_renderedTexture = 0;

private:
	friend class ModuleEditor;

	void UpdateProgram();

	void* m_context;

	GLuint m_depthrenderbuffer;
	GLuint m_program;
	Model3D* m_model3D;
	float4x4 m_model;
	const char* m_vertexShader = "default_vertex.glsl";
	const char* m_fragmentShader = "default_fragment.glsl";
};
