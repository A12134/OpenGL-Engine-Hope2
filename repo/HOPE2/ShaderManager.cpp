#include "ShaderManager.h"

LogManager* ShaderManager::mLogManager;

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
	mLogManager->addLog(ELogType::E_EVENT, "Unloading shaders.");
	mShaders.clear();
}

void ShaderManager::createNewShader(const std::string vertexShaderSource, const std::string shaderName)
{
	Shader* vertexShader = new Shader(EShaderType::EVertexShader, GL_VERTEX_SHADER);
	vertexShader->loadShaderSource(vertexShaderSource);

	mLogManager->addLog(ELogType::E_EVENT, "Loaded shaders.");

	ShaderProgram thisProgram = ShaderProgram(shaderName);
	thisProgram.linkShaders(vertexShader->getShader());

	mShaders.push_back(thisProgram);

	delete vertexShader;
	vertexShader = nullptr;
}

void ShaderManager::createNewShader(const std::string vertexShaderSource, const std::string fragmentShaderSource, const std::string shaderName)
{
	Shader* vertexShader = new Shader(EShaderType::EVertexShader, GL_VERTEX_SHADER);
	vertexShader->loadShaderSource(vertexShaderSource);

	Shader* fragmentShader = new Shader(EShaderType::EFragmentShader, GL_FRAGMENT_SHADER);
	fragmentShader->loadShaderSource(fragmentShaderSource);

	mLogManager->addLog(ELogType::E_EVENT, "Loaded shaders.");

	ShaderProgram thisProgram = ShaderProgram(shaderName);
	thisProgram.linkShaders(vertexShader->getShader(), fragmentShader->getShader());

	mShaders.push_back(thisProgram);

	delete vertexShader;
	vertexShader = nullptr;

	delete fragmentShader;
	fragmentShader = nullptr;
}

void ShaderManager::createNewShader(const std::string vertexShaderSource, const std::string fragmentShaderSource, const std::string geometryShaderSource, const std::string shaderName)
{
	Shader* vertexShader = new Shader(EShaderType::EVertexShader, GL_VERTEX_SHADER);
	vertexShader->loadShaderSource(vertexShaderSource);

	Shader* fragmentShader = new Shader(EShaderType::EFragmentShader, GL_FRAGMENT_SHADER);
	fragmentShader->loadShaderSource(fragmentShaderSource);

	Shader* geometryShader = new Shader(EShaderType::EGeometryShader, GL_GEOMETRY_SHADER);
	geometryShader->loadShaderSource(geometryShaderSource);

	mLogManager->addLog(ELogType::E_EVENT, "Loaded shaders.");

	ShaderProgram thisProgram = ShaderProgram(shaderName);
	thisProgram.linkShaders(vertexShader->getShader(), fragmentShader->getShader(), geometryShader->getShader());

	mShaders.push_back(thisProgram);

	delete vertexShader;
	vertexShader = nullptr;

	delete fragmentShader;
	fragmentShader = nullptr;

	delete geometryShader;
	geometryShader = nullptr;
}

ShaderProgram * ShaderManager::getShader(const std::string shaderName)
{
	for (unsigned int i = 0; i < mShaders.size(); i++)
	{
		if (mShaders.at(i).matchName(shaderName))
		{
			return &mShaders.at(i);
		}
	}
	mLogManager->addLog(ELogType::E_ERROR, "Shader " + shaderName + " does not exist!");
	mLogManager->errorExit();

	return nullptr;
}
