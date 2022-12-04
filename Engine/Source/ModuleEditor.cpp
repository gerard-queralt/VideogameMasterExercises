#include "ModuleEditor.h"

#include <string>

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "WindowMainMenu.h"
#include "WindowHardware.h"
#include "WindowConfiguration.h"
#include "WindowScene.h"

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

	m_windows.push_back(new WindowMainMenu());
	m_windows.push_back(m_console = new WindowConsole());
	m_windows.push_back(new WindowHardware());
	m_windows.push_back(m_model = new WindowModel3D());
	m_windows.push_back(new WindowConfiguration());
	m_windows.push_back(new WindowScene());

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
	for (std::list<Window*>::iterator it = m_windows.begin(); it != m_windows.end(); ++it) {
		(*it)->Draw();
	}

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
