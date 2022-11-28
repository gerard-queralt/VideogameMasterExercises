#pragma once
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"
#include "ModuleEditorCamera.h"
#include "ModuleRenderExercise.h"
#include "ModuleEditor.h"
#include "ModuleDebugDraw.h"
#include "ModuleTexture.h"

#include "MillisecondTimer.h"

using namespace std;

#define TIME_PER_FRAME 1000.f / 60.f // Approx. 60 fps

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(input = new ModuleInput());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(camera = new ModuleEditorCamera());
	modules.push_back(exercise = new ModuleRenderExercise());
	modules.push_back(debugDraw = new ModuleDebugDraw());
	modules.push_back(texture = new ModuleTexture());
	
	timer = new MillisecondTimer();
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

bool Application::Start()
{
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Start();

	timer->Start();
	m_prevTime = timer->Read();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	int currentTime = timer->Read();
	m_deltaTime = currentTime - m_prevTime;

	if (TIME_PER_FRAME < m_deltaTime){
		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			ret = (*it)->PreUpdate();

		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			ret = (*it)->Update();

		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			ret = (*it)->PostUpdate();

		m_prevTime = currentTime;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
