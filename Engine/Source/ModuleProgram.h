#pragma once

#include "Module.h"
#include <string>

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	unsigned int CreateProgramFromShaders(std::string vertexShaderName, std::string fragmentShaderName);

private:
	std::string readFile(std::string fileName);
};

