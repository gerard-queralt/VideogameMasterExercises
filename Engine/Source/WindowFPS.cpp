#include "WindowFPS.h"

#include "imgui.h"

#include "Application.h"

WindowFPS::WindowFPS() : Window("FPS")
{
	//all values will be zero
	m_fpsHist = std::vector<float>(m_fpsCaptures);
}

WindowFPS::~WindowFPS()
{
}

update_status WindowFPS::Update()
{
	bool enabled;

	if (ImGui::Begin(m_name.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		m_fpsHist[m_currentIndex] = App->GetDeltaTime();
		LOG_ENGINE(std::to_string(App->GetDeltaTime()).c_str());
		ImGui::PlotHistogram("Framerate Plot", &m_fpsHist[0], m_fpsCaptures);
		if (m_currentIndex < m_fpsCaptures - 1) {
			++m_currentIndex;
		}
		else {
			//remove the first element and increase the size of the vector back
			m_fpsHist.erase(m_fpsHist.begin());
			m_fpsHist.push_back(0);
		}
	}
	ImGui::End();
	return UPDATE_CONTINUE;
}
