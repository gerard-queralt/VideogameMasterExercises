#include "WindowRenderer.h"

#include "imgui.h"

#include "Application.h"
#include "ModuleRender.h"

int WindowRenderer::s_bufferSize = 128;

WindowRenderer::WindowRenderer() : SubWindow("Renderer")
{
	m_vertexShaderBuffer = App->renderer->GetVertexShader();
	m_fragmentShaderBuffer = App->renderer->GetFragmentShader();
}

WindowRenderer::~WindowRenderer()
{
}

void WindowRenderer::DrawWindowContents()
{
	ImGui::TextUnformatted("Vertex shader");
	ImGui::InputText("##vertex shader", &m_vertexShaderBuffer[0], s_bufferSize);
	ImGui::TextUnformatted("Fragment shader");
	ImGui::InputText("##fragment shader", &m_fragmentShaderBuffer[0], s_bufferSize);
	if (ImGui::Button("Update shaders")) {
		App->renderer->SetShaders(m_vertexShaderBuffer.c_str(), m_fragmentShaderBuffer.c_str());
	}
}
