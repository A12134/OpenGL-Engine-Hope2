#include "HLight.h"



HLight::HLight(glm::vec3 direction, glm::vec3 lightColor, float intensive)
{
	this->mParameter.type = HLightType::HDirectLight;
	this->mParameter.mDirection = direction;
	this->mParameter.mLightColor = lightColor;
	this->mParameter.mIntense = intensive;
}

HLight::HLight(glm::vec3 position, glm::vec3 lightColor, float intensive, glm::vec3 attenuation)
{
	this->mParameter.type = HLightType::HPointLight;
	this->mParameter.mPosition = position;
	this->mParameter.mLightColor = lightColor;
	this->mParameter.mIntense = intensive;
	this->mParameter.attenuation = attenuation;
}

HLight::~HLight()
{
}
