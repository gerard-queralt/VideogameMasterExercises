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

	GLuint CreateProgramFromShaders(const std::string& vertexShaderName, const std::string& fragmentShaderName);

private:
	std::string readShaderFile(const std::string& fileName);
	GLuint compileShader(GLenum shaderType, const std::string& shaderSource);
	GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
};

