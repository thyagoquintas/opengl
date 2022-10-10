#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"


class Window
{
public:
	Window();
	Window(GLint width, GLint height);
	~Window();
	int Initialize();
	bool ShouldClose() { return glfwWindowShouldClose(window); }
	void SwapBuffers() { return glfwSwapBuffers(window); }
	GLfloat GetBufferWidth() { return (float)bufferWidth; }
	GLfloat GetBufferHeight() { return (float)bufferHeight; }

	bool * getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

private:
	GLFWwindow* window;
	GLint width, height;
	int bufferWidth, bufferHeight;

	//Callback de mouse e teclado
	void createCallBacks();

	//configuração de teclado
	bool keys[1024];
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);

	//Configuração do mouse
	bool mouseFirstMove;
	GLfloat lastX, lastY, xChange, yChange;
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

