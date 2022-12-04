#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "glew.h"
#include "ModuleEditor.h"
#include "SDL_render.h"

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

	m_context = SDL_GL_CreateContext(App->window->m_window);

	GLenum err = glewInit();
	// … check for errors
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

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// The depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	return true;
}

update_status ModuleRender::PreUpdate()
{
	int window_width, window_height;
	SDL_GetWindowSize(App->window->m_window, &window_width, &window_height);
	glViewport(0, 0, window_width, window_height);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, /*m_framebuffer*/ 0);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // Render on the whole framebuffer, complete from the lower left corner to the upper right
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->m_window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG_ENGINE("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(m_context);

	return true;
}

void ModuleRender::WindowResized(unsigned i_width, unsigned i_height)
{
}
