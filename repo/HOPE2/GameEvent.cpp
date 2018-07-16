#include "GameEvent.h"

// static object pre-declaration
LogManager* GameEvent::mLogManager;


GameEvent::GameEvent(Window * _window)
{
	this->mCurrentState = EGameState::E_Debugging;
	this->mGameWindow = _window;
}

void GameEvent::setCurrentState(EGameState state)
{
	switch (state)
	{
	case EGameState::E_Debugging:
		// init debugging code here
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
}
