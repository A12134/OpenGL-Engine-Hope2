#include "SceneManager.h"

std::vector<Scene> SceneManager::mScenes;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

unsigned int SceneManager::createScene(std::string name)
{
	mScenes.push_back(Scene(name));
	return mScenes.size()-1;
}

void SceneManager::attachCameraToScene(SimpleCamera * cam, unsigned int sceneHandle)
{
	mScenes.at(sceneHandle).attachCamera(cam);
}

void SceneManager::renderScene(unsigned int sceneHandle)
{
	mScenes.at(sceneHandle).renderScene();
}

void SceneManager::updateScene(unsigned int sceneHandle)
{
	//TODO: update the scene
}
