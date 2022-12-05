#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "ModuleEditor.h"
#include "SDL_render.h"

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{
	glDeleteProgram(m_program);
	delete m_model3D;
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

	glEnable(GL_TEXTURE_2D);

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	// The texture we're going to render to
	glGenTextures(1, &m_renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_renderedTexture);

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

	// Set "m_renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderedTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	return true;
}

bool ModuleRender::Start()
{
	m_program = App->program->CreateProgramFromShaders(m_vertexShader, m_fragmentShader);

	m_model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f),
		float4x4::identity,
		float3(1.0f));

	SetModel3D((Model3D::s_modelFolderPath + "BakerHouse.fbx").c_str());

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
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	int window_width, window_height;
	SDL_GetWindowSize(App->window->m_window, &window_width, &window_height);
	glViewport(0, 0, window_width, window_height);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (m_model3D != nullptr)
		m_model3D->Draw();
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->m_window);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
	glBindTexture(GL_TEXTURE_2D, m_renderedTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, i_width, i_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderedTexture, 0);
}

void ModuleRender::SetModel3D(const char* i_modelPath)
{
	delete m_model3D;
	m_model3D = Model3D::LoadFromFile(i_modelPath);
	App->editor->SetTargetModel(m_model3D);
}
