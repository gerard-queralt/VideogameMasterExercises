#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

	void ResizeWindow(int i_width, int i_height);
	
	bool IsWindowFullscreen();
	bool IsWindowResizable();
	bool IsWindowBorderless();
	bool IsWindowDesktopFullscreen();

	void SetWindowToDefault();
	void SetFullscreen(bool i_fullscreen);
	void SetResizable(bool i_resizable);
	void SetBorderless(bool i_borderless);
	void SetDesktopFullscreen(bool i_fullDesktop);

public:
	//The window we'll be rendering to
	SDL_Window* m_window = NULL;

	//The surface contained by the window
	SDL_Surface* m_screenSurface = NULL;

private:
	SDL_bool BoolToSDL_Bool(bool i_bool);
	bool IsFlagSet(SDL_WindowFlags i_flag);

	//whether the window was set to regular fullscreen (true) or desktop fullscreen (false)
	//this is because both flags are set at the same time, so it's impossible to differentiate otherwise
	bool m_fullscreen = false;
};

#endif // __ModuleWindow_H__