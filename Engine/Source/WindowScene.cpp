#include "WindowScene.h"

#include "imgui.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

WindowScene::WindowScene() : Window("Scene")
{
}

WindowScene::~WindowScene()
{
}

void WindowScene::Draw()
{
	bool enabled;

	//App->renderer->CreateTextureFromContext();
	//App->window->CreateTextureFromSurface();

	if (ImGui::Begin(m_name.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::TextUnformatted("WIP");
		//ImGui::Image((void*)texture, ImVec2(1024, 1024));
	}
	ImGui::End();
}
