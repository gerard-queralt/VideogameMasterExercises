#include "WindowScene.h"

#include "imgui.h"

#include "Application.h"
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

	if (ImGui::Begin(m_name.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Image((void*)App->renderer->m_renderedTexture, ImVec2(1024, 1024), ImVec2(0, 1), ImVec2(1, 0));
	}
	ImGui::End();
}
