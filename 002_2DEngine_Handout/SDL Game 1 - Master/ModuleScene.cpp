#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

const std::string ModuleScene::PATH = "";

bool ModuleScene::Init()
{
    texture = App->textures->Load((PATH + "ken_stage.png").c_str());
    return true;
}

update_status ModuleScene::Update()
{
    bool res = App->renderer->Blit(texture, 0, 0, rect);
    if (res)
        return UPDATE_CONTINUE;
    return UPDATE_ERROR;
}
