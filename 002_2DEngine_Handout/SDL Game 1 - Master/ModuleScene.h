#pragma once

#include "Module.h"
#include <string>
#include "SDL/include/SDL_render.h"
#include "Globals.h"

class ModuleScene : public Module
{
private:
	static const std::string PATH;

	SDL_Texture* texture;
	SDL_Rect* rect;

public:
	bool Init();
	update_status Update();
};

