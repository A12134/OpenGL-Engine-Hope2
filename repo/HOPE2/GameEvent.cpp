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
	
	BaseCamera::mWindow = this->mGameWindow;
	mLogManager->addLog(ELogType::E_EVENT, "Hook cameras with the window.");
	
	// initilize all the class after this line that requires logManager. And don't forget to hook the logmanager
	
	this->mShaderManager = new ShaderManager();
	
	this->mTextureManager = new TextureManager();
	
	MeshManager::mTexManager = this->mTextureManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook texture Manager(Mesh Manager)");
	
	this->mMeshManager = new MeshManager();

	GameObject::mTexManager = this->mTextureManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Texture Manager(GameObject).");

	// init camera
	this->mCamera = new SimpleCamera(
		vec3(0.0f, 8.0f, 10.0f),
		vec3(0.0f, 0.0f, 0.0f),
		65.0f,
		1366.0f,
		768.0f,
		0.1f,
		1000.0f
	);
	mLogManager->addLog(ELogType::E_EVENT, "initializing Camera.");


	//--------------------- testing code ------------------

	mShaderManager->createNewShader("sampleVertexShader.glsl", "sampleFragmentShader.glsl", "sampleShader");

	Model::mMeshManager = this->mMeshManager;
	Model::mTexManager = this->mTextureManager;

	testingModel = new Model();
	mMeshManager->loadModel("assets/Hanger//Hangar.obj", testingModel->getRoot());

	// ----------------------------------------------------

}

void GameEvent::HookLogManager()
{
	Shader::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Shader).");
	
	ShaderProgram::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Shader Program).");
	
	ShaderManager::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Shader Manager).");
	
	BaseCamera::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Base Camera).");
	
	TextureManager::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Texture Manager).");
	
	GameObject::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Game Object).");
	
	MeshManager::mLogManager = this->mLogManager;
	mLogManager->addLog(ELogType::E_EVENT, "Hook Log Manager(Mesh Manager).");

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
	this->mCamera->update(deltaSeconds);
}

void GameEvent::debugRender()
{
	testingModel->render(mShaderManager->getShader("sampleShader"), mat4(1), this->mCamera->getViewMatrix(), this->mCamera->getProjectionMatrix(), testingModel->getRoot());
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
