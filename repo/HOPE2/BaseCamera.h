#ifndef BASE_CAMERA_H
#define BASE_CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"
#include "LogManager.h"

using namespace glm;

class BaseCamera
{
public:
	static Window* mWindow;

private:
	mat4 mProjection;

public:
	// perspective projection
	BaseCamera(float fov, float width, float height,float nearz, float farz);
	// orthographic projection
	BaseCamera(float left, float right, float bot, float top, float nearz, float farz);
	~BaseCamera();

	mat4 getProjectionMatrix() { return this->mProjection; };
};
#endif

