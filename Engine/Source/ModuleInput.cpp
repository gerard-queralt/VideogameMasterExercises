#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleEditorCamera.h"
#include "ModuleEditor.h"

#include "SDL/include/SDL.h"
#include "imgui_impl_sdl.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	App->editor->OutputToConsole("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
        std::string errorLog = "SDL_EVENTS could not initialize! SDL_Error: " + std::string(SDL_GetError()) + "\n";
        App->editor->OutputToConsole(errorLog.c_str());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    char* dropfileDir;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    int newWidth = sdlEvent.window.data1;
                    int newHeight = sdlEvent.window.data2;
                    App->renderer->WindowResized(newWidth, newHeight);
                }
                if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE)
                    return UPDATE_STOP;
                break;
            case SDL_DROPFILE:
                dropfileDir = sdlEvent.drop.file;
                App->editor->OutputToConsole(("File dropped: " + std::string(dropfileDir)).c_str());
                App->renderer->SetModel3D(dropfileDir);
                break;
        }
    }

    m_keyboard = SDL_GetKeyboardState(NULL);
    int deltaTime = App->GetDeltaTime();

    //translate camera
    float3 deltaPosVec = float3::zero;
    if (m_keyboard[SDL_SCANCODE_LSHIFT])
        m_cameraSpeed *= 2;
    float deltaPos = m_cameraSpeed * deltaTime;

    if (m_keyboard[SDL_SCANCODE_W]) {
        deltaPosVec.x += deltaPos;
    }
    if (m_keyboard[SDL_SCANCODE_S]) {
        deltaPosVec.x -= deltaPos;
    }
    if (m_keyboard[SDL_SCANCODE_Q]) {
        deltaPosVec.y += deltaPos;
    }
    if (m_keyboard[SDL_SCANCODE_E]) {
        deltaPosVec.y -= deltaPos;
    }
    if (m_keyboard[SDL_SCANCODE_D]) {
        deltaPosVec.z += deltaPos;
    }
    if (m_keyboard[SDL_SCANCODE_A]) {
        deltaPosVec.z -= deltaPos;
    }
    App->camera->Translate(deltaPosVec);

    //rotate camera
    float3 deltaRot = float3::zero;
    float deltaAngle = m_angleSpeed * deltaTime;

    if (m_keyboard[SDL_SCANCODE_LEFT]) {
        deltaRot.y += deltaAngle;
    }
    if (m_keyboard[SDL_SCANCODE_RIGHT]) {
        deltaRot.y -= deltaAngle;
    }
    if (m_keyboard[SDL_SCANCODE_UP]) {
        deltaRot.x += deltaAngle;
    }
    if (m_keyboard[SDL_SCANCODE_DOWN]) {
        deltaRot.x -= deltaAngle;
    }
    App->camera->Rotate(deltaRot);

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
    LOG_ENGINE("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
