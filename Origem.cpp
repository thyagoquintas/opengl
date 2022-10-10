#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Window* window;
Camera camera;

//Vertex Shader
static const char* vertexLocation = "VertexShader.glsl";
static const char* fragmentLocation = "FragmentShader.glsl";

void CriaTriangulos() {
	GLfloat vertices[] = {
		//x , y		
		-1.0f, -1.0f, 0.0f,         //Vertice 1 (Preto)
		0.0f, 1.0f, 0.0f,           //Vertice 0 (Verde)
		1.0f, -1.0f, 0.0f,          //Vertice 2 (Vermelho)
		0.0f, -1.0f, 1.0f            //Vertice 3 (Azul)
	};

	GLuint indices[] = {
		0, 1, 2,
		1, 2, 3,
		0, 1, 3,
		0, 2, 3
	};
	
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, sizeof(vertices), indices, sizeof(indices));
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, sizeof(vertices), indices, sizeof(indices));
	meshList.push_back(obj2);
}

void CreateShader() {
	Shader* shader = new Shader();
	shader->CreateFromFile(vertexLocation, fragmentLocation);
	shaderList.push_back(shader);
}


int main() {
	window = new Window(1024,768);
	window->Initialize();

	CriaTriangulos();
	CreateShader();

	//Criando a camera
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.05f, 0.05f);

	//Variaveis para controle da movimentação do triangulo
	bool direction = true, sizeDirection = true, angleDirection = true; //true=direita e false=esquerda
	float triOffset = 0.0f, maxOffset = 0.7f, minOffset = -0.7f, incOffset = 0.01f;
	float size = 0.4f, maxSize = 0.7f, minSize = -0.7f, incSize = 0.01f;
	float angle = 0.0f, maxAngle = 360.0f, minAngle = -1.0f, incAngle = 0.5f;
	
	while (!window->ShouldClose()) {

		//Habilitar os eventos de usuario
		glfwPollEvents();

		//Camera controla o teclado e mouse
		camera.KeyControl(window->getKeys());
		camera.MouseControl(window->getXChange(), window->getYChange());

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Desenha o triangulo
		Shader * shader = shaderList[0];
		shader->UseProgram();

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

				/*
				* Triangulo 1
				*/
				meshList[0]->RenderMesh();
				//criar uma matriz 4x4 (1.0f)
				glm::mat4 model(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, -0.25f, -1.5f)); //Movimentações do triangulo
				model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4)); //Tamanho do triangulo
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotação
				
				glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model)); //Envia os dados para o triangulo

				/*
				* Triangulo 2
				*/
				meshList[1]->RenderMesh();
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f)); //Movimentações do triangulo
				model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4)); //Tamanho do triangulo
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, -1.0f, 0.0f)); //Rotação
				glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model)); //Envia os dados para o triangulo


				//Projeção de perspectiva 3D
				glm::mat4 projection = glm::perspective(1.0f, window->GetBufferWidth() / window->GetBufferHeight(), 0.1f, 100.0f);
				glUniformMatrix4fv(shader->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection)); //Envia os dados para o triangulo

				glUniformMatrix4fv(shader->GetUniformView(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));


		glUseProgram(0);

		window->SwapBuffers();
	}

	window->~Window();
	return 0;
}