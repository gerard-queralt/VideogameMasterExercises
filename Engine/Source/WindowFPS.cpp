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
		int deltaTime = App->GetDeltaTime();
		float timePerFrame = App->GetMsPerFrame();
		float fps = deltaTime / timePerFrame;
		m_fpsHist[m_currentIndex] = fps;
		LOG_ENGINE(std::to_string(fps).c_str());
		
		ImGui::PlotHistogram("Framerate Plot", &m_fpsHist[0], m_fpsCaptures, 0, "", 0.f, 160.f, ImVec2(310, 160));
		
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
