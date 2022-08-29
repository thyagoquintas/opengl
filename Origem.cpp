#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"


int main() {
	if (!glfwInit()) {
		printf("GLFW: Nao pode ser iniciado");
		return 1;
	}

	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "Ola Mundo!", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW: Nao foi poss�vel criar a janela");
		glfwTerminate();
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	if (glewInit() != GLEW_OK) {
		printf("Glew: Nao pode ser iniciado!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);


	while (!glfwWindowShouldClose(mainWindow)) {

		//Habilitar os eventos de usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}