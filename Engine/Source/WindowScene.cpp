#include "WindowScene.h"

#include "imgui.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleEditorCamera.h"

WindowScene::WindowScene() : Window("Scene")
{
}

WindowScene::~WindowScene()
{
}

void WindowScene::Draw()
{
	bool enabled;

	if (ImGui::Begin(m_name.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNavInputs)) {
		ManageResize();
		ImGui::Image((void*)App->renderer->m_renderedTexture, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
	}
	ImGui::End();
}

void WindowScene::ManageResize()
{
	ImVec2 availableRegion = ImGui::GetContentRegionAvail();
	bool widthChanged = m_previousWidht != availableRegion.x;
	bool heightChanged = m_previousHeight != availableRegion.y;
	if (widthChanged || heightChanged) { // window was resized
		App->camera->SetAspectRatio(availableRegion.x / availableRegion.y);
		m_previousWidht = availableRegion.x;
		m_previousHeight = availableRegion.y;
	}
}
