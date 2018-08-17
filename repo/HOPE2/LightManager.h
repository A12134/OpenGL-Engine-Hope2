#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H
#include "HLight.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class LightManager
{
private:
	static std::vector<HLight> mLights;
public:
	LightManager();
	~LightManager();

	static void startUp();
	static void shutDown();

	static unsigned int createNewDirectionLight(glm::vec3 direction, glm::vec3 lightColor, float intensive);

	static unsigned int createNewPointLight(glm::vec3 position, glm::vec3 lightColor, float intensive, glm::vec3 attenuation);

	static unsigned int getLightNum() { return mLights.size(); }

	static HLight* getLight(unsigned int index) { return &mLights.at(index); };
};
#endif

