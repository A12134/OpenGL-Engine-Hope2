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

void ShaderProgram::setUniform1f(const char * var, float f1)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform1f(loc, f1);
}

void ShaderProgram::setUniform2f(const char * var, float f1, float f2)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform2f(loc, f1, f2);
}

void ShaderProgram::setUniform3f(const char * var, float f1, float f2, float f3)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform3f(loc, f1, f2, f3);
}

void ShaderProgram::setUniform4f(const char * var, float f1, float f2, float f3, float f4)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform4f(loc, f1, f2, f3, f4);
}

void ShaderProgram::setUniform1i(const char * var, int i1)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform1i(loc, i1);
}

void ShaderProgram::setUniform2i(const char * var, int i1, int i2)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform2i(loc, i1, i2);
}

void ShaderProgram::setUniform3i(const char * var, int i1, int i2, int i3)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform3i(loc, i1, i2, i3);
}

void ShaderProgram::setUniform4i(const char * var, int i1, int i2, int i3, int i4)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform4i(loc, i1, i2, i3, i4);
}

void ShaderProgram::setUniform1ui(const char * var, unsigned int ui1)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform1ui(loc, ui1);
}

void ShaderProgram::setUniform2ui(const char * var, unsigned int ui1, unsigned int ui2)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform2ui(loc, ui1, ui2);
}

void ShaderProgram::setUniform3ui(const char * var, unsigned int ui1, unsigned int ui2, unsigned int ui3)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform3ui(loc, ui1, ui2, ui3);
}

void ShaderProgram::setUniform4ui(const char * var, unsigned int ui1, unsigned int ui2, unsigned int ui3, unsigned int ui4)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform4ui(loc, ui1, ui2, ui3, ui4);
}

void ShaderProgram::setUniform2fv(const char * var, glm::vec2 vec2)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform2fv(loc, 1, glm::value_ptr(vec2));
}

void ShaderProgram::setUniform3fv(const char * var, glm::vec3 vec3)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform3fv(loc, 1, glm::value_ptr(vec3));
}

void ShaderProgram::setUniform4fv(const char * var, glm::vec4 vec4)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform4fv(loc, 1, glm::value_ptr(vec4));
}

void ShaderProgram::setUniform2iv(const char * var, glm::ivec2 ivec2)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform2iv(loc, 1, glm::value_ptr(ivec2));
}

void ShaderProgram::setUniform3iv(const char * var, glm::ivec3 ivec3)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform3iv(loc, 1, glm::value_ptr(ivec3));
}

void ShaderProgram::setUniform4iv(const char * var, glm::ivec4 ivec4)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform4iv(loc, 1, glm::value_ptr(ivec4));
}

/*
void ShaderProgram::setUniform1uiv(const char * var, glm::uvec1 uvec1)
{
GLint loc = glGetUniformLocation(this->mProgramID, var);
glUniform1uiv(loc, 1, glm::value_ptr(uvec1));
}*/

void ShaderProgram::setUniform2uiv(const char * var, glm::uvec2 uvec2)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform2uiv(loc, 1, glm::value_ptr(uvec2));
}

void ShaderProgram::setUniform3uiv(const char * var, glm::uvec3 uvec3)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform3uiv(loc, 1, glm::value_ptr(uvec3));
}

void ShaderProgram::setUniform4uiv(const char * var, glm::uvec4 uvec4)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniform4uiv(loc, 1, glm::value_ptr(uvec4));
}

void ShaderProgram::setUniformMatrix2x2fv(const char * var, glm::mat2 mat2, GLboolean transpose)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniformMatrix2fv(loc, 1, transpose, glm::value_ptr(mat2));
}

void ShaderProgram::setUniformMatrix3x3fv(const char * var, glm::mat3 mat3, GLboolean transpose)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniformMatrix3fv(loc, 1, transpose, glm::value_ptr(mat3));
}

void ShaderProgram::setUniformMatrix4x4fv(const char * var, glm::mat4 mat4, GLboolean transpose)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniformMatrix4fv(loc, 1, transpose, glm::value_ptr(mat4));
}

void ShaderProgram::setUniformMatrix2x3fv(const char * var, glm::mat2x3 mat2x3, GLboolean transpose)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniformMatrix2x3fv(loc, 1, transpose, glm::value_ptr(mat2x3));
}

void ShaderProgram::setUniformMatrix3x2fv(const char * var, glm::mat3x2 mat3x2, GLboolean transpose)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniformMatrix3x2fv(loc, 1, transpose, glm::value_ptr(mat3x2));
}

void ShaderProgram::setUniformMatrix2x4fv(const char * var, glm::mat2x4 mat2x4, GLboolean transpose)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniformMatrix2x4fv(loc, 1, transpose, glm::value_ptr(mat2x4));
}

void ShaderProgram::setUniformMatrix4x2fv(const char * var, glm::mat4x2 mat4x2, GLboolean transpose)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniformMatrix4x2fv(loc, 1, transpose, glm::value_ptr(mat4x2));
}

void ShaderProgram::setUniformMatrix3x4fv(const char * var, glm::mat3x4 mat3x4, GLboolean transpose)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniformMatrix3x4fv(loc, 1, transpose, glm::value_ptr(mat3x4));
}

void ShaderProgram::setUniformMatrix4x3fv(const char * var, glm::mat4x3 mat4x3, GLboolean transpose)
{
	GLint loc = glGetUniformLocation(this->mProgramID, var);
	glUniformMatrix4x3fv(loc, 1, transpose, glm::value_ptr(mat4x3));
}