#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

const float ModuleScene::DELTA_X_FRAME_INC = 10.f;

#define PATH ""
#define SCALE 5
#define MIN_DELTA_X 0
#define MAX_DELTA_X 768 * SCALE - SCREEN_WIDTH * (SCALE/1.5f)

bool ModuleScene::Start()
{
    texture = App->textures->Load(((std::string(PATH)) + "ken_stage.png").c_str());
    
    rectBackground = new SDL_Rect();
    rectBackground->x = 72;
    rectBackground->y = 208;
    rectBackground->w = 768;
    rectBackground->h = 176;
    
    rectGround = new SDL_Rect();
    rectGround->x = 8;
    rectGround->y = 392;
    rectGround->w = 896;
    rectGround->h = 72;

    deltaX = 0.f;
    
    return true;
}

update_status ModuleScene::Update()
{
    if (deltaX < MIN_DELTA_X)
        deltaX = MIN_DELTA_X;
    if (deltaX > MAX_DELTA_X) {
        deltaX = MAX_DELTA_X;
    }
    bool res = App->renderer->Blit(texture, -deltaX, 0.f, rectBackground->w * SCALE, rectBackground->h * SCALE, rectBackground);
    res = App->renderer->Blit(texture, -deltaX, rectBackground->h * SCALE, rectGround->w * SCALE, rectGround->h * SCALE, rectGround);
    if (res)
        return UPDATE_CONTINUE;
    return UPDATE_ERROR;
}
