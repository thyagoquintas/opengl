#include <GL/glew.h>
#include <iostream>

class Shader
{
public:
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void UseProgram();

	GLint GetUniformProjection() { return uniformProjection; };
	GLint GetUniformModel() { return uniformModel; };

private:
	GLuint shaderId;
	GLint uniformProjection, uniformModel;


	void Compile(const char* vertexCode, const char* fragmentCode);

};

