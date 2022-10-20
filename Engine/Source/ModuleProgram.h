#pragma once

#include "Module.h"
#include <string>
#include <glew.h>

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	static const std::string SHADER_FOLDER_PATH;

	unsigned int CreateProgramFromShaders(std::string vertexShaderName, std::string fragmentShaderName);

private:
	std::string readShaderFile(std::string fileName);
	GLuint compileShader(GLenum shaderType, std::string shaderSource);
};

