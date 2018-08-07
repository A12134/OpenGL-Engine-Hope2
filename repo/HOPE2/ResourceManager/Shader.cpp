#include "Shader.h"
#include <sstream>
#include <fstream>
#include <iostream>

LogManager* Shader::mLogManager;


Shader::Shader(EShaderType type, GLint ID)
{
	this->mShaderType = type;
	this->mShaderAddress = glCreateShader(ID);
	std::string tmpType;
	switch (type)
	{
	case EShaderType::EVertexShader:
		tmpType = "Vertex Shader";
		break;
	case EShaderType::EGeometryShader:
		tmpType = "Geometry Shader";
		break;
	case EShaderType::EFragmentShader:
		tmpType = "Fragment Shader";
		break;
	default:
		tmpType = "";
		break;
	}
	mLogManager->addLog(ELogType::E_EVENT, "Create " + tmpType + ".");
}

void Shader::loadShaderSource(const std::string & filePath)
{
	std::ifstream file;
	file.open(filePath.c_str());

	if (!file.good())
	{
		mLogManager->addLog(ELogType::E_ERROR, "Cannot find " + filePath + ".");
		mLogManager->errorExit();
	}

	std::stringstream stream;
	stream << file.rdbuf();
	file.close();
	mLogManager->addLog(ELogType::E_EVENT, "Load shader source from " + filePath + ".");

	std::string mShaderSource = stream.str();
	const char* sourceChar = mShaderSource.c_str();
	glShaderSource(this->mShaderAddress, 1, &sourceChar, NULL);
	glCompileShader(this->mShaderAddress);

	int success;
	char infoLog[512];
	glGetShaderiv(this->mShaderAddress, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->mShaderAddress, 512, NULL, infoLog);
		std::string infoLogStr = infoLog;
		mLogManager->addLog(ELogType::E_ERROR, "Fail to compile shader source from " + filePath + ":\n" + infoLogStr);
		mLogManager->errorExit();
	}

	mLogManager->addLog(ELogType::E_EVENT, "Compiled " + filePath + ".");
}

Shader::~Shader()
{
}
