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

	void UpdateSize(int i_windowWidth, int i_windowHeight);
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

	int m_windowWidth = SCREEN_WIDTH;
	int m_windowHeight = SCREEN_HEIGHT;

private:
	SDL_bool BoolToSDL_Bool(bool i_bool);
};

#endif // __ModuleWindow_H__