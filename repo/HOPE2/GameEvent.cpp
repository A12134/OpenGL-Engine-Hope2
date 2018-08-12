#include "GameEvent.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Hangar.h"


GameEvent::GameEvent(Window * _window)
{
	this->setCurrentState(EGameState::E_Debugging);
	this->mGameWindow = _window;

	HookLogManager(); 
	
	BaseCamera::mWindow = this->mGameWindow;
	LogManager::addLog(ELogType::E_EVENT, "Hook cameras with the window.");
	
	// initilize all the class after this line that requires logManager. And don't forget to hook the logmanager
	
	this->mShaderManager = new ShaderManager();
	
	this->mTextureManager = new TextureManager();
	

	// init camera
	this->mCamera = new SimpleCamera(
		vec3(0.0f, 5.0f, -10.0f),
		vec3(0.0f, 0.0f, 0.0f),
		65.0f,
		1920.0f,
		1440.0f,
		0.1f,
		1000.0f
	);
	LogManager::addLog(ELogType::E_EVENT, "initializing Camera.");


	//--------------------- testing code ------------------

	mShaderManager->createNewShader("skyboxVertexShader.glsl", "skyboxFragmentShader.glsl", "skyboxShader");
	mShaderManager->createNewShader("sampleVertexShader.glsl", "sampleFragmentShader.glsl", "sampleShader");

	SkyBox::mTexManager = this->mTextureManager;

	this->testingSkyBox = new SkyBox(mShaderManager->getShader("skyboxShader"));

	// ----------------------------------------------------



}

void GameEvent::HookLogManager()
{	

}

void GameEvent::setCurrentState(EGameState state)
{
	switch (state)
	{
	case EGameState::E_Debugging:
		// init debugging code here
		LogManager::addLog(ELogType::E_EVENT, "(Game Event State)Enter Debugging state.");
		break;
	default:
		break;
	}
}

void GameEvent::debugUpdate(float deltaSeconds)
{
	this->mCamera->update(deltaSeconds);
}

void GameEvent::debugRender()
{
	testingSkyBox->render(this->mCamera->getViewMatrix(), this->mCamera->getProjectionMatrix());
	/*for (unsigned int i = 0; i < this->mGameObjects.size(); i++)
	{
		this->mGameObjects.at(i)->render(this->mCamera);
	}*/
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

	delete mCamera;
	mCamera = nullptr;

	delete mShaderManager;
	mShaderManager = nullptr;

	mGameWindow = nullptr;
}
