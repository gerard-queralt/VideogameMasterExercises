#include "ModuleProgram.h"
#include <fstream>

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

unsigned int ModuleProgram::CreateProgramFromShaders(std::string vertexShaderName, std::string fragmentShaderName)
{
	std::string vertexShaderCode = readFile(vertexShaderName);
	std::string fragmentShaderCode = readFile(fragmentShaderName);

	return 0;
}

std::string ModuleProgram::readFile(std::string fileName)
{
	std::ifstream file;
	std::string fileContents = "";
	std::string fileLine;

	file.open(fileName);

	if (file.is_open()) {
		while (std::getline(file, fileLine)) {
			fileContents += fileLine + "\n";
		}
		file.close();
	}

	return fileContents;
}
