#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "Window.h"
#include "LogManager.h"
#include "GameEvent.h"

#define RESOLUTION_X 1366	// window width
#define RESOLUTION_Y 768	// window height

int main() 
{

	// initialization
	LogManager* engineLog = new LogManager();

	engineLog->addLog(ELogType::E_EVENT, "Hook Log Manager(Window).");
	Window::mLogManager = engineLog;
	engineLog->addLog(ELogType::E_EVENT, "Hook Log Manager(GameEvent).");
	GameEvent::mLogManager = engineLog;

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
	//mainWindow->enableFaceCulling();

	engineLog->addLog(ELogType::E_EVENT, "Initializing Game events.");
	GameEvent* gameEvent = new GameEvent(mainWindow);
	engineLog->addLog(ELogType::E_EVENT, "Finish initialization, starting ticks.");

	// main loop
	float OTSS = 0;		// old time since loop start
	while (!glfwWindowShouldClose(mainWindow->getWindow()))
	{
		float TSS = (float)glfwGetTime();	// time since loop start
		float deltaSec = TSS - OTSS;		// calculate deltaSeconds
		OTSS = TSS;
		mainWindow->clearColor(0.0f, 0.0f, 0.0f, 1.0f);
		mainWindow->clearBuffers();

		// loop throught gameEvent
		gameEvent->update(deltaSec);
		gameEvent->render();

		mainWindow->swapBuffer();
		glfwPollEvents();	
	}
	
	engineLog->addLog(ELogType::E_EVENT, "Engine shutdown.");

	delete gameEvent;
	gameEvent = nullptr;

	delete mainWindow;
	mainWindow = nullptr;

	delete engineLog;
	engineLog = nullptr;

	return 0;
}