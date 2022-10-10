#include "Shader.h"

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
	Compile(vertexCode, fragmentCode);
}

void Shader::CreateFromFile(const char* vertexLocation, const char* fragmentLocation){
	std::string vertexCode = ReadFile(vertexLocation);
	std::string fragmentCode = ReadFile(fragmentLocation);

	Compile(vertexCode.c_str(), fragmentCode.c_str());
}

std::string Shader::ReadFile(const char* fileLocation) {
	std::string content = "";
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Arquivo não foi encontrado (%s)", fileLocation);
		return "";
	}

	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode) {
	shaderId = glCreateProgram(); //Cria um programa

	GLuint _vShader = glCreateShader(GL_VERTEX_SHADER); //Cria um shader
	GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER); //Cria um shader

	//Gambiarra para converter Char em GLChar
	const GLchar* vCode[1];
	const GLchar* fCode[1];
	vCode[0] = vertexCode; //Codigo do vShader
	fCode[0] = fragmentCode; //Codigo do fShader

	glShaderSource(_vShader, 1, vCode, NULL); //Associa o shader ao codigo
	glCompileShader(_vShader); //Compila o shader
	glAttachShader(shaderId, _vShader); //Adiciona o shader ao programa

	glShaderSource(_fShader, 1, fCode, NULL); //Associa o shader ao codigo
	glCompileShader(_fShader); //Compila o shader
	glAttachShader(shaderId, _fShader); //Adiciona o shader ao programa

	glLinkProgram(shaderId); //Adiciona o programa

	uniformModel = glGetUniformLocation(shaderId, "model"); //Encontra a entrada do modelo
	uniformProjection = glGetUniformLocation(shaderId, "projection"); //Encontra a entrada de projeção
	uniformView = glGetUniformLocation(shaderId, "view"); //Encontra a entrada de projeção
}

void Shader::UseProgram() {
	glUseProgram(shaderId);
}

Shader::Shader() {
	shaderId = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

Shader::~Shader() {
	if (shaderId != 0) {
		glDeleteProgram(shaderId);
	}
}
