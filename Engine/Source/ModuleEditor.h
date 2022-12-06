#pragma once

#include "Module.h"

#include <list>

#include "EditorWindow.h"
#include "WindowMainMenu.h"
#include "WindowConsole.h"
#include "WindowModel3D.h"
#include "WindowScene.h"
#include "Model3D.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void OutputToConsole(const char* i_textToPrint);
	void SetTargetModel(const Model3D* i_model);
	bool IsSceneFocused();

private:
	std::list<EditorWindow*> m_windows;
	WindowMainMenu* m_mainMenu = nullptr;
	WindowConsole* m_console = nullptr;
	WindowModel3D* m_model = nullptr;
	WindowScene* m_scene = nullptr;
};

