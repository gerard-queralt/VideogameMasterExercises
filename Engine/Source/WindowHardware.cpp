#include "WindowHardware.h"

#include <cmath>

#include "imgui.h"
#include "glew.h"
#include "SDL.h"

WindowHardware::WindowHardware() : Window("Hardware")
{
	m_sdlVersion = std::to_string(SDL_MAJOR_VERSION) + "." + std::to_string(SDL_MINOR_VERSION) + "." + std::to_string(SDL_PATCHLEVEL);

	int cacheSizeInB = SDL_GetCPUCacheLineSize();
	int cacheSizeInKB = std::ceil(cacheSizeInB / 1000.f);
	int cacheSizeInKb = cacheSizeInKB * 8;
	m_cpusAndCache = std::to_string(SDL_GetCPUCount()) + " (Cache: " + std::to_string(cacheSizeInKb) + "kb)";

	int ramInMB = SDL_GetSystemRAM();
	float ramInGB = ramInMB / 1000.f;
	float ramInGb = ramInGB * 8.f;
	//this is the value multiplied by 10 to the power of 8
	//insted of to the power of 9, which is what Giga is
	//this is to make rounding easier,
	//since I can't find a way to set decimal precision
	int ramInGbOneDecimalAux = std::ceil(ramInGb * 10.f);
	std::string ramInGbOneDecimal = std::to_string(ramInGbOneDecimalAux);
	//insert a dot in the penultimate position
	ramInGbOneDecimal.insert(ramInGbOneDecimal.length() - 1, ".");
	m_ram = ramInGbOneDecimal + "Gb";
}

WindowHardware::~WindowHardware()
{
}

void WindowHardware::Start()
{
	char glVendor[128];
	sprintf(glVendor, "%s", glGetString(GL_VENDOR));
	m_gpuVendor = _strdup(glVendor);
	char glRenderer[128];
	sprintf(glRenderer, "%s", glGetString(GL_RENDERER));
	m_gpuBrand = _strdup(glRenderer);
}

update_status WindowHardware::Update()
{
	bool enabled;

	if (ImGui::Begin(m_name.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::TextUnformatted(("SDL Version: " + m_sdlVersion).c_str());

		ImGui::Separator();

		ImGui::TextUnformatted(("CPUs: " + m_cpusAndCache).c_str());
		ImGui::TextUnformatted(("System RAM: " + m_ram).c_str());

		ImGui::Separator();

		ImGui::TextUnformatted(("GPU: " + m_gpuVendor).c_str());
		ImGui::TextUnformatted(("Brand: " + m_gpuBrand).c_str());
	}
	ImGui::End();

	return UPDATE_CONTINUE;
}