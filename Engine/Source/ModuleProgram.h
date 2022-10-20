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
	std::string ReadShaderFile(const std::string& fileName);
	GLuint CompileShader(GLenum shaderType, const std::string& shaderSource);
	GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader);
};

