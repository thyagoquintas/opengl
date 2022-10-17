#include "GL/glew.h"
#include "stb_image.h"

class Texture
{
public:
	Texture();
	~Texture();
	Texture(char* fileName);

	void loadTexture();
	void clearTexture();
	void useTexture();

private:
	GLuint textureID;
	int width, height, bitDepth;
	char* fileLocation;
};

