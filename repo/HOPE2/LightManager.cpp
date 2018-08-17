#include "LightManager.h"

std::vector<HLight> LightManager::mLights;

LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}

unsigned int LightManager::createNewDirectionLight(glm::vec3 direction, glm::vec3 lightColor, float intensive)
{
	mLights.push_back(HLight(direction, lightColor, intensive));
	return mLights.size() - 1;
}

unsigned int LightManager::createNewPointLight(glm::vec3 position, glm::vec3 lightColor, float intensive, glm::vec3 attenuation)
{
	mLights.push_back(HLight(position, lightColor, intensive, attenuation));
	return mLights.size() - 1;
}

