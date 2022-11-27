#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleInput;
class ModuleProgram;
class ModuleEditorCamera;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleDebugDraw;
class ModuleTexture;
class ModuleTimer;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleEditorCamera* camera = nullptr;
	ModuleRenderExercise* exercise = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleTimer* timer = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
