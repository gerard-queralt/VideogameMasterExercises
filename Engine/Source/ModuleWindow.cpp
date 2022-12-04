#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	App->editor->OutputToConsole("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::string sdlError = "SDL_VIDEO could not initialize! SDL_Error: " + std::string(SDL_GetError()) + "\n";
		App->editor->OutputToConsole(sdlError.c_str());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		m_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(m_window == NULL)
		{
			std::string sdlError = "Window could not be created! SDL_Error: " + std::string(SDL_GetError()) + "\n";
			App->editor->OutputToConsole(sdlError.c_str());
			ret = false;
		}
		else
		{
			//Get window surface
			
			m_screenSurface = SDL_GetWindowSurface(m_window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG_ENGINE("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(m_window != NULL)
	{
		SDL_DestroyWindow(m_window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::ResizeWindow(int i_width, int i_height)
{
	SDL_SetWindowSize(m_window, i_width, i_height);
}

void ModuleWindow::SetWindowToDefault()
{
	SDL_SetWindowFullscreen(m_window, 0);
	SDL_SetWindowResizable(m_window, SDL_FALSE);
	SDL_SetWindowBordered(m_window, SDL_TRUE);
	m_screenSurface = SDL_GetWindowSurface(m_window);
}

void ModuleWindow::SetFullscreen(bool i_fullscreen)
{
	SetWindowToDefault();
	if (i_fullscreen) {
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
		m_screenSurface = SDL_GetWindowSurface(m_window);
	}
}

void ModuleWindow::SetResizable(bool i_resizable)
{
	SetWindowToDefault();
	SDL_SetWindowResizable(m_window, BoolToSDL_Bool(i_resizable));
}

void ModuleWindow::SetBorderless(bool i_borderless)
{
	SetWindowToDefault();
	//this call sets borders, so it's the opposite of what we want
	//thus the negation
	SDL_SetWindowBordered(m_window, BoolToSDL_Bool(!i_borderless));
}

void ModuleWindow::SetDesktopFullscreen(bool i_fullDesktop)
{
	SetWindowToDefault();
	if (i_fullDesktop) {
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		m_screenSurface = SDL_GetWindowSurface(m_window);
	}
}

GLuint ModuleWindow::CreateTextureFromSurface()
{
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_screenSurface->w, m_screenSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_screenSurface->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

	return texture;
}

SDL_bool ModuleWindow::BoolToSDL_Bool(bool i_bool)
{
	if (i_bool)
		return SDL_TRUE;
	return SDL_FALSE;
}
