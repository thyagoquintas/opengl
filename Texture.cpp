#include "Texture.h"

Texture::Texture(){
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = NULL;
}

Texture::~Texture(){
	
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = NULL;
}

Texture::Texture(char* fileName)
{
	clearTexture();
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileName;
}

void Texture::loadTexture(){
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	if (!texData) {
		printf("Erro ao carregar a imagem %s", fileLocation);
	}
	glGenTextures(1, &textureID); //Gera um endereço de estrutura na memória
	glBindTexture(GL_TEXTURE_2D, textureID); //Bind do tamanho do endereço da memória
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Eixo X
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Eixo Y
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Filtro para distância curta
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Filtro para longa distância
	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData); //Carrega na memória

		//Mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0); //Remove o endereço do apontamento
	stbi_image_free(texData); //Remove a imagem da memória 
}

void Texture::clearTexture(){
	glDeleteTextures(1, &textureID);
}

void Texture::useTexture(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}
