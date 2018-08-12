#include "SimpleCamera.h"

double SimpleCamera::mMouseXNew = 0.0f;
double SimpleCamera::mMouseYNew = 0.0f;
bool SimpleCamera::mChangeViewAngle = false;

SimpleCamera::SimpleCamera(vec3 camPos, vec3 camTarget, float fov, float width, float height, float nearz, float farz):
	BaseCamera(fov, width, height, nearz, farz)
{
	setupCamera(camPos, camTarget);
}

SimpleCamera::SimpleCamera(vec3 camPos, vec3 camTarget, float left, float right, float bot, float top, float nearz, float farz):
	BaseCamera(left, right, bot, top, nearz, farz)
{
	setupCamera(camPos, camTarget);
}

SimpleCamera::~SimpleCamera()
{
	LogManager::addLog(ELogType::E_EVENT, "Destory Camera Object.");
}

void SimpleCamera::setupCamera(vec3 camPos, vec3 camTarget)
{
	this->mUp = vec3(0.0f, 1.0f, 0.0f);
	this->mCamPos = camPos;
	this->mCamTarget = camTarget;										// not used
	this->mTargetToPos = normalize(this->mCamPos - this->mCamTarget);	// not used
	this->mCamRight = normalize(cross(this->mUp, this->mTargetToPos));
	this->mCamUp = cross(this->mTargetToPos, this->mCamRight);
	this->mCamFront = vec3(0.0f, 0.0f, 1.0f);
	this->mCameraSpeed = 5.0f;
	this->mCameraSensitivity = 0.05f;
	this->mYaw = 0.0f;
	this->mPitch = 0.0f;

	// register camera's mouse callback function
	glfwSetCursorPosCallback(this->mWindow->getWindow(), getMousePosition_CallBack);
	glfwSetMouseButtonCallback(this->mWindow->getWindow(), getMouseButton_CallBack);
}

void SimpleCamera::inputController(float deltaSec)
{
	if (glfwGetKey(this->mWindow->getWindow(), GLFW_KEY_W))
	{
		this->mCamPos += this->mCamFront * this->mCameraSpeed * deltaSec;
	}
	if (glfwGetKey(this->mWindow->getWindow(), GLFW_KEY_S))
	{
		this->mCamPos -= this->mCamFront * this->mCameraSpeed * deltaSec;
	}
	if (glfwGetKey(this->mWindow->getWindow(), GLFW_KEY_A))
	{
		this->mCamPos -= this->mCamRight * this->mCameraSpeed * deltaSec;
	}
	if (glfwGetKey(this->mWindow->getWindow(), GLFW_KEY_D))
	{
		this->mCamPos += this->mCamRight * this->mCameraSpeed * deltaSec;
	}
	if (this->mChangeViewAngle)
	{
		double deltaMouseX = SimpleCamera::mMouseXNew - this->mMouseXLast;
		double deltaMouseY = SimpleCamera::mMouseYNew - this->mMouseYLast;

		deltaMouseX *= this->mCameraSensitivity;
		deltaMouseY *= this->mCameraSensitivity;

		this->mYaw += deltaMouseX;
		this->mPitch += deltaMouseY;

		if (this->mPitch > 89.0f)
		{
			this->mPitch = 89.0f;
		}
		if (this->mPitch < -89.0f)
		{
			this->mPitch = -89.0f;
		}

		this->mCamFront.x = cos(radians(this->mPitch))*sin(radians(this->mYaw));
		this->mCamFront.y = sin(radians(this->mPitch));
		this->mCamFront.z = cos(radians(this->mPitch))*cos(radians(mYaw));
		this->mCamFront = normalize(this->mCamFront);
	}
}

mat4 SimpleCamera::getViewMatrix()
{
	mat4 view = mat4(1);
	view = glm::lookAt(this->mCamPos, this->mCamPos + this->mCamFront, this->mCamUp);
	return view;
}

void SimpleCamera::update(float deltaSec)
{
	// recalculate camera up vector
	inputController(deltaSec);
	this->mCamRight = normalize(cross(this->mCamFront, this->mUp));
	this->mCamUp = normalize(cross(this->mCamRight, this->mCamFront));
	mMouseXLast = SimpleCamera::mMouseXNew;
	mMouseYLast = SimpleCamera::mMouseYNew;
}

void SimpleCamera::getMousePosition_CallBack(GLFWwindow * window, double _mouseX, double _mouseY)
{
	SimpleCamera::mMouseXNew = _mouseX;
	SimpleCamera::mMouseYNew = _mouseY;
}

void SimpleCamera::getMouseButton_CallBack(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		SimpleCamera::mChangeViewAngle = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		SimpleCamera::mChangeViewAngle = false;
	}
}
