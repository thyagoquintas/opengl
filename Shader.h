#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>

class Shader
{
public:
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);
	void UseProgram();

	GLint GetUniformProjection() { return uniformProjection; };
	GLint GetUniformModel() { return uniformModel; };

private:
	GLuint shaderId;
	GLint uniformProjection, uniformModel;

	std::string ReadFile(const char* fileLocation);
	void Compile(const char* vertexCode, const char* fragmentCode);

};

