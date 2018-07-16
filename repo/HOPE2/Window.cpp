#include "Window.h"

LogManager* Window::mLogManager;

Window::Window(int width, int height, const char * title, GLFWmonitor * monitor, GLFWwindow * share)
{
	if (!mLogManager)
	{
		MessageBox(
			NULL,
			"Engine Log Manager failed to initalize!",
			"Ooooooooooooooooops error!",
			MB_OK);
	}

	mWindow = glfwCreateWindow(width, height, title, monitor, share);
	

	if (mWindow == nullptr)
	{
		mLogManager->addLog(ELogType::E_ERROR, "Failed to create window.");
		mLogManager->errorExit();
	}

	mLogManager->addLog(ELogType::E_EVENT, "Window created.");
}

Window::~Window()
{
	mLogManager->addLog(ELogType::E_EVENT, "Destory window object");
	glfwDestroyWindow(mWindow);
	mWindow = nullptr;
	mLogManager = nullptr;
}

void Window::activateContext()
{
	if (glfwGetCurrentContext() != mWindow)
	{
		glfwMakeContextCurrent(mWindow);
		mLogManager->addLog(ELogType::E_EVENT, "Window context activated");
	}
}

GLFWwindow * Window::getWindow()
{
	return mWindow;
}

void Window::createViewport(int x, int y, int _x, int _y)
{
	glViewport(x, y, _x, _y);
	mLogManager->addLog(ELogType::E_EVENT, "Created viewport.");
}

void Window::enableDepthTest()
{
	activateContext();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	mLogManager->addLog(ELogType::E_EVENT, "Enabling Depth test. Depth Function: Less");
}

void Window::enableMSAA()
{
	activateContext();
	glEnable(GL_MULTISAMPLE);
	mLogManager->addLog(ELogType::E_EVENT, "Enabling multi-sample anti aliasing");
}

void Window::enableFaceCulling()
{
	activateContext();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	mLogManager->addLog(ELogType::E_EVENT, "Enabling face culling, Cull Face: Back");
}

void Window::clearColor(float r, float g, float b, float a)
{
	activateContext();
	glClearColor(r, g, b, a);
}

void Window::clearColor(glm::vec3 color, float alpha)
{
	activateContext();
	glClearColor(color.r, color.g, color.b, alpha);
}

void Window::clearColor(glm::vec4 color)
{
	activateContext();
	glClearColor(color.r, color.g, color.b, color.a);
}

void Window::clearBuffers()
{
	activateContext();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::freezeWindowSize(int x, int y)
{
	glfwSetWindowSizeLimits(mWindow, x, y, x, y);
}

void Window::swapBuffer()
{
	glfwSwapBuffers(mWindow);
}
