#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "LogManager.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
private:
	std::string mProgramName;
	unsigned int mProgramID;

public:
	static LogManager* mLogManager;
public:
	ShaderProgram(const std::string shaderName);
	~ShaderProgram();

	void linkShaders(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader);

	void linkShaders(unsigned int vertexShader, unsigned int fragmentShader);

	void linkShaders(unsigned int vertexShader);
	
	void checkLinkStatus();
};
#endif

