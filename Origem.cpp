#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLuint VAO, VBO, programa;


//Vertex Shader
static const char* vShader = "                                \n\
#version 330                                                  \n\
                                                              \n\
layout(location=0) in vec2 pos;                               \n\
uniform mat4 model;                                           \n\
                                                              \n\
void main(){                                                  \n\
	gl_Position = model * vec4(pos, 1.0, 1.0);                \n\
}";

static const char* fShader = "                                \n\
#version 330                                                  \n\
                                                              \n\
uniform vec3 triangleColor;                                   \n\
out vec4 color;                                               \n\
                                                              \n\
void main(){                                                  \n\
	color = vec4(triangleColor, 1.0);                         \n\
}";



void CriaTriangulos() {
	GLfloat vertices[] = {
		//x , y		
		0.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};

	glGenVertexArrays(1, &VAO); //Cria o VAO
	glBindVertexArray(VAO); //Coloca o VAO em contexto
		glGenBuffers(1, &VBO); //Cria o VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO); //Coloca o VBO em contexto
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Explica o valor do Array
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); //Explica os valores de x e y
		glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //remover do contexto o VBO
	glBindVertexArray(0); //remover do contexto o VAO
}


void CompilaShader() {
	programa = glCreateProgram(); //Cria um programa
	GLuint _vShader = glCreateShader(GL_VERTEX_SHADER); //Cria um shader
	GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER); //Cria um shader

	//Gambiarra para converter Char em GLChar
	const GLchar* vCode[1];
	const GLchar* fCode[1];
	vCode[0] = vShader; //C�digo do vShader
	fCode[0] = fShader; //C�digo do fShader

	glShaderSource(_vShader, 1, vCode, NULL); //associa o shader ao codigo
	glCompileShader(_vShader); //Compila o shader
	glAttachShader(programa, _vShader); //Adiciona o shader ao programa

	glShaderSource(_fShader, 1, fCode, NULL); //associa o shader ao codigo
	glCompileShader(_fShader); //Compila o shader
	glAttachShader(programa, _fShader); //Adiciona o shader ao programa

	glLinkProgram(programa); //Adiciona o programa

}

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

	CriaTriangulos();
	CompilaShader();

	//Variaveis para controle da movimentação do triangulo
	bool direction = true, sizeDirection = true, angleDirection = true; //true=direita e false=esquerda
	float triOffset = 0.0f, maxOffset = 0.7f, minOffset = -0.7f, incOffset = 0.01f;
	float size = 0.4f, maxSize = 0.7f, minSize = -0.7f, incSize = 0.01f;
	float angle = 0.0f, maxAngle = 360.0f, minAngle = -1.0f, incAngle = 0.1f;
	
	while (!glfwWindowShouldClose(mainWindow)) {

		//Habilitar os eventos de usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Desenha o triangulo
		glUseProgram(programa);
			glBindVertexArray(VAO);
				/*
				* Desenha o triangulo
				*/
				glDrawArrays(GL_TRIANGLES, 0, 3);

				/*
				* Alterando a cor do triangulo
				*/
				GLuint uniColor = glGetUniformLocation(programa, "triangleColor");
				float r = (float)rand()/RAND_MAX;
				float g = (float)rand()/RAND_MAX;
				float b = (float)rand()/RAND_MAX;
				glUniform3f(uniColor, r, g, b);

				/*
				* Mover nosso triangulo
				*/
				if (triOffset >= maxOffset || triOffset <= minOffset)
					direction = !direction;
				triOffset += direction ? incOffset : incOffset * -1;

				if (size >= maxSize || size <= minSize)
					sizeDirection = !sizeDirection;
				size += sizeDirection ? incSize : incSize * -1;
				
				if (angle >= maxAngle || angle <= minAngle)
					angleDirection = !angleDirection;
				angle += angleDirection ? incAngle : incAngle * -1;
				printf("%f\n", angle);

				//criar uma matriz 4x4 (1.0f)
				glm::mat4 model(1.0f);

				//Movimentações do triangulo
				model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f));

				//Tamanho do triangulo
				model = glm::scale(model, glm::vec3(size, size, 1.0));

				//Rotação
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

				GLuint uniModel = glGetUniformLocation(programa, "model");
				glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

			glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}