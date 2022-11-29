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
class Timer;

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

	int GetDeltaTime() {
		return m_deltaTime;
	}

	float GetMsPerFrame() {
		return m_millisecondsPerFrame;
	}

	void SetMsPerFrame(float i_millisecondsPerFrame) {
		m_millisecondsPerFrame = i_millisecondsPerFrame;
	}

private:
	std::list<Module*> modules;

	float m_millisecondsPerFrame = 1000.f / 60.f; // Approx. 60 fps

	Timer* m_timer = nullptr;
	int m_prevTime = 0;
	int m_deltaTime = 0;
};

extern Application* App;
