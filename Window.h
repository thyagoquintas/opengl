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


private:
	GLFWwindow* window;
	GLint width, height;
	int bufferWidth, bufferHeight;

	//Callback de mouse e teclado
	void createCallBacks();

	//configuração de teclado
	bool keys[1024];
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);


};

