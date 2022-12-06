#pragma once

#include "EditorWindow.h"

#include <string>

class WindowHardware : public EditorWindow
{
public:
	WindowHardware();
	~WindowHardware();

	void DrawWindowContents();

private:
	std::string m_sdlVersion;
	std::string m_cpusAndCache;
	std::string m_ram;
	std::string m_gpuVendorAndDevice;
	std::string m_gpuBrand;
};

