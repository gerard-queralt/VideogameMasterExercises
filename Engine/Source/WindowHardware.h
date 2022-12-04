#pragma once

#include "Window.h"

#include <string>

class WindowHardware : public Window
{
public:
	WindowHardware();
	~WindowHardware();

	void Draw();

private:
	std::string m_sdlVersion;
	std::string m_cpusAndCache;
	std::string m_ram;
	std::string m_gpuVendorAndDevice;
	std::string m_gpuBrand;
};

