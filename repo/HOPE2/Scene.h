#ifndef SCENE_H
#define SCENE_H
#include "HObject.h"
#include "HAudio.h"
#include <vector>
#include "ResourceManager.h"
#include "SimpleCamera.h"
class Scene
{
private:
	std::string mSceneName;
	std::vector<HObject*> mObjects;
	SimpleCamera* cam;

public:
	Scene(std::string name);
	~Scene();

	void attachCamera(SimpleCamera* _cam) { cam = _cam; }

	void addObjectToScene(HObject* obj) { mObjects.push_back(obj); }

	void renderScene();
};
#endif

