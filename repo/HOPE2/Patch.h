#ifndef PATCH_H
#define PATCH_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct Patch
{
	glm::vec4 mEmission;
	float mReflectance;
	glm::vec4 mIncident;
	glm::vec4 mExcident;
};

#endif