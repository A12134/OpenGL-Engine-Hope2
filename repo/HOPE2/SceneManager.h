#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include "Scene.h"
#include <vector>
#include "SimpleCamera.h"
class SceneManager
{
private:
	static std::vector<Scene> mScenes;

public:
	SceneManager();
	~SceneManager();

	// @return: return the handle of the scene
	static unsigned int createScene(std::string sceneName);

	static void attachCameraToScene(SimpleCamera* cam, unsigned int sceneHandle);

	static void renderScene(unsigned int sceneHandle);

	static void updateScene(unsigned int sceneHandle);
};
#endif

