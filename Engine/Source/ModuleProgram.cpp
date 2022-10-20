#include "ModuleProgram.h"
#include <fstream>

const std::string ModuleProgram::SHADER_FOLDER_PATH = "";

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

unsigned int ModuleProgram::CreateProgramFromShaders(std::string vertexShaderName, std::string fragmentShaderName)
{
	std::string vertexShaderCode = readShaderFile(vertexShaderName);
	std::string fragmentShaderCode = readShaderFile(fragmentShaderName);

	return 0;
}

std::string ModuleProgram::readShaderFile(std::string fileName)
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

GLuint ModuleProgram::compileShader(GLenum shaderType, std::string shaderSource)
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
			LOG("Log Info: %s", info);
			free(info);
		}
	}
	return shaderID;
}
