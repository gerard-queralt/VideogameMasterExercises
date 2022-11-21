#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "glew.h"
#include "ModuleEditor.h"

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	App->editor->OutputToConsole("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits

	context = SDL_GL_CreateContext(App->window->window);

	GLenum err = glewInit();
	// � check for errors
	char glewVersion[128];
	sprintf(glewVersion, "Using Glew %s", glewGetString(GLEW_VERSION));
	App->editor->OutputToConsole(glewVersion);
	// Should be 2.0

	char glVendor[128];
	sprintf(glVendor, "Vendor: %s", glGetString(GL_VENDOR));
	App->editor->OutputToConsole(glVendor);
	char glRenderer[128];
	sprintf(glRenderer, "Renderer: %s", glGetString(GL_RENDERER));
	App->editor->OutputToConsole(glRenderer);
	char glSupported[128];
	sprintf(glSupported, "OpenGL version supported %s", glGetString(GL_VERSION));
	App->editor->OutputToConsole(glSupported);
	char glslVersion[128];
	sprintf(glslVersion, "GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	App->editor->OutputToConsole(glslVersion);

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	return true;
}

update_status ModuleRender::PreUpdate()
{
	int window_width, window_height;
	SDL_GetWindowSize(App->window->window, &window_width, &window_height);
	glViewport(0, 0, window_width, window_height);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG_ENGINE("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
}

