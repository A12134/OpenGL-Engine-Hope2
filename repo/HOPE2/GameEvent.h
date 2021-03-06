#ifndef GAME_EVENT_H
#define GAME_EVENT_H
#include "Window.h"
#include "LogManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Model.h"
#include "SkyBox.h"

enum class EGameState 
{
	E_Debugging
};

class GameEvent
{

private:
	EGameState mCurrentState;			// game state
	Window * mGameWindow;				// game window
	ShaderManager* mShaderManager;		// GLSL shader manager
	SimpleCamera* mCamera;				// game Camera
	TextureManager* mTextureManager;	// game texture Manager

	std::vector<GameObject*> mGameObjects;

	/*------------------------Testing Class----------------------*/
	Model* testingModel;
	SkyBox* testingSkyBox;

	// Playing around codes
	unsigned int fbo;
	unsigned int screenColorBuffer;
	unsigned int rboDepthStencil;

public:
	GameEvent(Window* _window);

public:
	void HookLogManager();

public:
	EGameState getCurrentState() { return mCurrentState; }
	void setCurrentState(EGameState state);

	void debugUpdate(float deltaSeconds);
	void debugRender();

public:
	void update(float deltaSeconds);
	void render();

public:
	~GameEvent();
};
#endif

