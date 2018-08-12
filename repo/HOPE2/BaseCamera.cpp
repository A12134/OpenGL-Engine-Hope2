#include "BaseCamera.h"
Window* BaseCamera::mWindow;

BaseCamera::BaseCamera(float fov, float width, float height, float nearz, float farz)
{
	this->mProjection = perspective(radians(fov), width/height, nearz, farz);
}

BaseCamera::BaseCamera(float left, float right, float bot, float top, float nearz, float farz)
{
	this->mProjection = ortho(left, right, bot, top, nearz, farz);
}

BaseCamera::~BaseCamera()
{
}
