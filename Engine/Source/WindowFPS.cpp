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

	if (ImGui::CollapsingHeader(m_name.c_str())) {
		float maxFPS = App->GetFPS();
		ImGui::SliderFloat("Max FPS", &maxFPS, 0.f, 120.f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
		App->SetFPS(maxFPS);
		
		int deltaTime = App->GetDeltaTime();
		m_fpsHist[m_currentIndex] = 1000.f / deltaTime;
		
		char currentFramerate[25];
		sprintf_s(currentFramerate, 25, "Framerate %.1f", m_fpsHist[m_currentIndex]);
		ImGui::PlotHistogram("##framerate", &m_fpsHist[0], m_fpsCaptures, 0, currentFramerate, 0.f, 160.f, ImVec2(310, 160));
		
		if (m_currentIndex < m_fpsCaptures - 1) {
			++m_currentIndex;
		}
		else {
			//remove the first element and increase the size of the vector back
			m_fpsHist.erase(m_fpsHist.begin());
			m_fpsHist.push_back(0);
		}
	}

	return UPDATE_CONTINUE;
}
