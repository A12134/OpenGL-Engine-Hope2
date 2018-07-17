#include "GameEvent.h"
#include "Shader.h"
#include "ShaderProgram.h"

// static object pre-declaration
LogManager* GameEvent::mLogManager;


GameEvent::GameEvent(Window * _window)
{
	this->setCurrentState(EGameState::E_Debugging);
	this->mGameWindow = _window;
	HookLogManager(); 
	// initilize all the class after this line that requires logManager. And don't forget to hook the logmanager
	this->mShaderManager = new ShaderManager();
}

void GameEvent::HookLogManager()
{
	Shader::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Shader).");
	ShaderProgram::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Shader Program).");
	ShaderManager::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Shader Manager).");
}

void GameEvent::setCurrentState(EGameState state)
{
	switch (state)
	{
	case EGameState::E_Debugging:
		// init debugging code here
		mLogManager->addLog(ELogType::E_EVENT, "(Game Event State)Enter Debugging state.");
		break;
	default:
		break;
	}
}

void GameEvent::debugUpdate(float deltaSeconds)
{
}

void GameEvent::debugRender()
{
}

void GameEvent::update(float deltaSeconds)
{
	switch (mCurrentState)
	{
	case EGameState::E_Debugging:
		debugUpdate(deltaSeconds);
		break;
	default:
		break;
	}
}

void GameEvent::render()
{
	switch (mCurrentState)
	{
	case EGameState::E_Debugging:
		debugRender();
		break;
	default:
		break;
	}
}

GameEvent::~GameEvent()
{
	mGameWindow = nullptr;
}
