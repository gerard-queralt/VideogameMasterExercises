#pragma once

#include "Module.h"
#include <string>
#include "SDL/include/SDL_render.h"
#include "Globals.h"

class ModuleScene : public Module
{
private:
	SDL_Texture* texture;
	SDL_Rect* rectBackground;
	SDL_Rect* rectGround;

public:
	static const float DELTA_X_FRAME_INC;

	bool Start();
	update_status Update();

	float deltaX;
};

