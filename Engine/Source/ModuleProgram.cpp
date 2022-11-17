#include "ModuleProgram.h"

#include <fstream>
#include "Application.h"
#include "ModuleEditor.h"

const std::string ModuleProgram::SHADER_FOLDER_PATH = "shaders/";

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

GLuint ModuleProgram::CreateProgramFromShaders(const std::string& vertexShaderName, const std::string& fragmentShaderName)
{
	std::string vertexShaderCode = ReadShaderFile(vertexShaderName);
	std::string fragmentShaderCode = ReadShaderFile(fragmentShaderName);

	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

	GLuint program = CreateProgram(vertexShader, fragmentShader);

	return program;
}

std::string ModuleProgram::ReadShaderFile(const std::string& fileName)
{
	std::ifstream file;
	std::string fileContents = "";
	std::string fileLine;

	file.open(SHADER_FOLDER_PATH + fileName);

	if (file.is_open()) {
		while (std::getline(file, fileLine)) {
			fileContents += fileLine + "\n";
		}
		file.close();
	}

	return fileContents;
}

GLuint ModuleProgram::CompileShader(GLenum shaderType, const std::string& shaderSource)
{
	GLuint shaderID = glCreateShader(shaderType);
	const char* sourceAsChars = shaderSource.c_str();
	glShaderSource(shaderID, 1, &sourceAsChars, 0);
	glCompileShader(shaderID);

	int res = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE) {
		int len = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &len);
		if (len > 0) {
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shaderID, len, &written, info);
			App->editor->OutputToConsole(("Log Info: " + std::string(info)).c_str());
			free(info);
		}
	}
	return shaderID;
}

GLuint ModuleProgram::CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	int res = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, &res);
	if (res == GL_FALSE) {
		int len = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(programID, len, &written, info);
			LOG_ENGINE("Program Log Info: %s", std::string(info));
			free(info);
		}
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return programID;
}
