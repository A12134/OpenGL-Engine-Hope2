#include "SimpleCamera.h"

LogManager* SimpleCamera::mLogManager;


SimpleCamera::SimpleCamera(vec3 camPos, vec3 camTarget, float fov, float width, float height, float nearz, float farz):
	BaseCamera(fov, width, height, nearz, farz)
{

}

SimpleCamera::SimpleCamera(vec3 camPos, vec3 camTarget, float left, float right, float bot, float top, float nearz, float farz):
	BaseCamera(left, right, bot, top, nearz, farz)
{
}

SimpleCamera::~SimpleCamera()
{
}
