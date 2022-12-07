#include "WindowScene.h"

#include "imgui.h"

#include "Application.h"
#include "Modules/ModuleRender.h"
#include "Modules/ModuleEditorCamera.h"

WindowScene::WindowScene() : EditorWindow("Scene")
{
	m_flags |= ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNavInputs;
}

WindowScene::~WindowScene()
{
}

void WindowScene::DrawWindowContents()
{
	ManageResize();
	ImGui::Image((void*)App->renderer->m_renderedTexture, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
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
