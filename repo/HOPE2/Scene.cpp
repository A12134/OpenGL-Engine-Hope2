#include "Scene.h"


Scene::Scene(std::string name)
{
	mSceneName = name;
}


Scene::~Scene()
{
}

void Scene::renderScene()
{
	for (unsigned int i = 0; i < mObjects.size(); i++)
	{
		std::vector<HMaterial*> mats;
		for (unsigned int j = 0; j < mObjects.at(i)->getMatNum(); j++) 
		{
			mats.push_back(ResourceManager::getMaterialAt(mObjects.at(i)->getMatAtObjectAtIndex(j)));
		}
		mObjects.at(i)->render(cam, mats);
	}
}
