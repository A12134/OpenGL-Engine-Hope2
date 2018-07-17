#ifndef SIMPLE_CAMERA_H
#define SIMPLE_CAMER_H
#include "BaseCamera.h"
#include "LogManager.h"
class SimpleCamera:
	public BaseCamera
{
public:
	static double mMouseXNew, mMouseYNew;

private:
	float mCameraSpeed;
	float mCameraSensitivity;
	vec2 mLastFrameMousePos;
	double mMouseXLast, mMouseYLast;
	static bool mChangeViewAngle;
	double mYaw, mPitch;

protected:
	vec3 mCamPos;
	vec3 mCamTarget;
	vec3 mCamUp;
	vec3 mCamRight;
	vec3 mUp;
	vec3 mTargetToPos;
	vec3 mCamFront;
public:
	SimpleCamera(vec3 camPos, vec3 camTarget,
		float fov, float width, float height, float nearz, float farz);
	SimpleCamera(vec3 camPos, vec3 camTarget,
		float left, float right, float bot, float top, float nearz, float farz);
	~SimpleCamera();

private:
	void setupCamera(vec3 camPos, vec3 camTarget);
	void inputController(float deltaSec);

public:
	mat4 getViewMatrix();

	void update(float deltaSec);

public:

	// callbacks 
	static void getMousePosition_CallBack(GLFWwindow* window, double _mouseX, double _mouseY);
	static void getMouseButton_CallBack(GLFWwindow* window, int button, int action, int mods);

};
#endif
