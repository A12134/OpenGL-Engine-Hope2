#ifndef WINDOW_H
#define WINDOW_H
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "LogManager.h"

class Window
{
private:
	GLFWwindow * mWindow;
public:
	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	~Window();

	void activateContext();

	GLFWwindow* getWindow();
	
	void createViewport(int x, int y, int _x, int _y);
	
	void enableDepthTest();

	void enableMSAA();

	void enableFaceCulling();
	
	void clearColor(float r, float g, float b, float a);
	
	void clearColor(glm::vec3 color, float alpha);
	
	void clearColor(glm::vec4 color);

	void clearBuffers();

	void freezeWindowSize(int x, int y);

	void swapBuffer();
};
#endif