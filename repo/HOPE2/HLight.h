/*The light class of the engine*/
/*Contains 2 types of the light, point light, and direction light*/
#ifndef H_LIGHT_H
#define H_LIGHT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class HLightType
{
	HPointLight,
	HDirectLight
};

struct HLightParam 
{
	HLightType type;
	glm::vec3 mPosition;	// light position, only used by point light
	glm::vec3 mDirection;	// light direction, only used by direct light
	glm::vec3 mLightColor;	// the color of the light
	float mIntense;			// the strength of the light
	glm::vec3 attenuation;	// 3 attenuation lvl, stored in vector 3, used only by point light
};
class HLight
{
private:
	HLightParam mParameter;
public:
	// Directional light constructor
	HLight(glm::vec3 direction, glm::vec3 lightColor, float intensive);
	
	// Point light constructor
	HLight(glm::vec3 position, glm::vec3 lightColor, float intensive, glm::vec3 attenuation);
	~HLight();

	HLightParam* getParam() { return &mParameter; }
};
#endif
