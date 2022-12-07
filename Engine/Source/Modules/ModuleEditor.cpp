#include "ModuleEditor.h"

#include <string>

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "Models/Windows/WindowMainMenu.h"
#include "Models/Windows/EditorWindows/WindowHardware.h"
#include "Models/Windows/EditorWindows/WindowConfiguration.h"
#include "Models/Windows/EditorWindows/WindowScene.h"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
	for (Window* window : m_windows)
		delete window;
	m_windows.clear();
}

bool ModuleEditor::Init()
{
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	m_windows.push_back(m_console = new WindowConsole());
	m_windows.push_back(new WindowHardware());
	m_windows.push_back(m_model = new WindowModel3D());
	m_windows.push_back(new WindowConfiguration());
	m_windows.push_back(m_scene = new WindowScene());

	m_mainMenu = new WindowMainMenu(m_windows);

	return true;
}

bool ModuleEditor::Start()
{
	ImGui_ImplSDL2_InitForOpenGL(App->window->m_window, App->renderer->m_context);
	ImGui_ImplOpenGL3_Init("#version 130");

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->m_window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGuiID dockSpaceId = ImGui::GetID("DockSpace");
	
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	
	ImGuiWindowFlags dockSpaceWindowFlags = 0;
	dockSpaceWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
	dockSpaceWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", nullptr, dockSpaceWindowFlags);
	ImGui::PopStyleVar(3);
	ImGui::DockSpace(dockSpaceId);
	ImGui::End();

	m_mainMenu->Draw();
	int windowIndex = 0;
	for (std::list<EditorWindow*>::iterator it = m_windows.begin(); it != m_windows.end(); ++it) {
		bool windowEnabled = m_mainMenu->IsWindowEnabled(windowIndex);
		(*it)->Draw(windowEnabled);
		m_mainMenu->SetWindowEnabled(windowIndex, windowEnabled);
		++windowIndex;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

	return true;
}

void ModuleEditor::OutputToConsole(const char* i_textToPrint)
{
	m_console->Output(i_textToPrint);
}

void ModuleEditor::SetTargetModel(const Model3D* i_model)
{
	m_model->SetModel(i_model);
}

bool ModuleEditor::IsSceneFocused()
{
	return m_scene->IsFocused();
}
