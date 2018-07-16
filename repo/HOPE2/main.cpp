#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "Window.h"
#include "LogManager.h"

#define RESOLUTION_X 1366	// window width
#define RESOLUTION_Y 768	// window height

int main() 
{

	// initialization
	LogManager* engineLog = new LogManager();

	Window::mLogManager = engineLog;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);	// multisample buffer

	Window* mainWindow = new Window(RESOLUTION_X, RESOLUTION_Y, "Main Window", NULL, NULL);
	mainWindow->activateContext();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		engineLog->addLog(ELogType::E_ERROR, "Failed to initialize GLAD proc.");
		engineLog->errorExit();
	}

	mainWindow->createViewport(0, 0, RESOLUTION_X, RESOLUTION_Y);
	mainWindow->freezeWindowSize(RESOLUTION_X, RESOLUTION_Y);
	mainWindow->enableDepthTest();
	mainWindow->enableMSAA();
	mainWindow->enableFaceCulling();
	engineLog->addLog(ELogType::E_EVENT, "Finish initialization, starting ticks.");

	// main loop
	while (!glfwWindowShouldClose(mainWindow->getWindow()))
	{
		mainWindow->clearColor(1.0f, 1.0f, 1.0f, 1.0f);
		mainWindow->clearBuffers();

		mainWindow->swapBuffer();
		glfwPollEvents();	
	}
	
	engineLog->addLog(ELogType::E_EVENT, "Engine shutdown.");
	delete mainWindow;
	mainWindow = nullptr;

	delete engineLog;
	engineLog = nullptr;

	return 0;
}