#include "Window.h"

Window::Window(){
	width = 800;
	height = 600;
}

Window::Window(GLint width, GLint height){
	Window::width = width;
	Window::height = height;
}

Window::~Window(){
	glfwDestroyWindow(window);
	glfwTerminate();
}

int Window::Initialize(){
	for (int i = 0; i < 1024; i++) {
		keys[i] = false;
	}

	if (!glfwInit()) {
		printf("GLFW: Nao pode ser iniciado");
		return 1;
	}

	window = glfwCreateWindow(width, height, "Nova Janela", NULL, NULL);
	if (!window) {
		printf("GLFW: Nao foi possivel criar a janela");
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("Glew: Nao pode ser iniciado!");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);
	glfwSetWindowUserPointer(window, this);
	createCallBacks();
	return 0;
}

void Window::createCallBacks(){
	glfwSetKeyCallback(window, handleKeys);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			printf("Pressed: %d\n", key);
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			printf("Relessed: %d\n", key);
		}
	}
}