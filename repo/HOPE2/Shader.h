#ifndef SHADER_H
#define SHADER_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "LogManager.h"
#include <string>

enum class EShaderType 
{
	EVertexShader,
	EGeometryShader,
	EFragmentShader
};

class Shader
{
private:
	//std::string mShaderSource;
	unsigned int mShaderAddress;
	EShaderType mShaderType;

public:
	Shader(EShaderType type, GLint ID);

	void loadShaderSource(const std::string &filePath);

	unsigned int getShader() { return mShaderAddress; }

	~Shader();
};
#endif

