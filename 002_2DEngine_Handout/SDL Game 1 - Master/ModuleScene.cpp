#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

const std::string ModuleScene::PATH = "";

bool ModuleScene::Init()
{
    texture = App->textures->Load((PATH + "ken_stage.png").c_str());
    rect = new SDL_Rect();
    rect->x = 0;
    rect->y = 0;
    rect->w = SCREEN_WIDTH;
    rect->h = SCREEN_HEIGHT;
    return true;
}

update_status ModuleScene::Update()
{
    bool res = App->renderer->Blit(texture, 0, 0, rect);
    if (res)
        return UPDATE_CONTINUE;
    return UPDATE_ERROR;
}
