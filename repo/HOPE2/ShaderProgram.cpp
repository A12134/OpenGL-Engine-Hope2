#include "ShaderProgram.h"

LogManager* ShaderProgram::mLogManager;


ShaderProgram::ShaderProgram(const std::string shaderName)
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::linkShaders(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader)
{
	glAttachShader(this->mProgramID, vertexShader);
	glAttachShader(this->mProgramID, fragmentShader);
	glAttachShader(this->mProgramID, geometryShader);
	mLogManager->addLog(ELogType::E_EVENT, "Links vertex, geometry and fragment shader to the program.");
	checkLinkStatus();
}

void ShaderProgram::linkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
	glAttachShader(this->mProgramID, vertexShader);
	glAttachShader(this->mProgramID, fragmentShader);
	mLogManager->addLog(ELogType::E_EVENT, "Links vertex and fragment shader to the program.");
	checkLinkStatus();
}

void ShaderProgram::linkShaders(unsigned int vertexShader)
{
	glAttachShader(this->mProgramID, vertexShader);
	mLogManager->addLog(ELogType::E_EVENT, "Links vertex shader to the program.");
	checkLinkStatus();
}

void ShaderProgram::checkLinkStatus()
{
	glLinkProgram(this->mProgramID);
	int success;
	char infoLog[512];
	glGetProgramiv(this->mProgramID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(this->mProgramID, 512, NULL, infoLog);
		std::string infoLogStr = infoLog;
		mLogManager->addLog(ELogType::E_ERROR, "Shader program linking failed.\n" + infoLogStr);
		mLogManager->errorExit();
	}
}
