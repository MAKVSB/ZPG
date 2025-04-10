#include "Texture.h"

void Texture::loadCubeMapFace(GLenum target, std::string path, bool flip) {
	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	if (ilLoadImage((const ILstring)path.c_str())) {
		if (flip) {
			iluFlipImage();
		}
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		glTexImage2D(target, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
	}
	ilDeleteImages(1, &imageID);
}


void Texture::loadTexture2D(std::string path, bool flip)
{
	if (textureType != -1) return;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	loadCubeMapFace(GL_TEXTURE_2D, path, flip);
	glGenerateMipmap(GL_TEXTURE_2D);

	// should be default parameters but whatever
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);


	textureType = GL_TEXTURE_2D;
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::createCubeMap(std::vector<std::string> faces, std::string basePath)
{
	if (textureType != -1) return;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	// Specify each face of the cube map and load the respective image
	for (int i = 0; i < 6; i++)
	{
		loadCubeMapFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, basePath + faces[i]);
	}

	// Set cube map parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	textureType = GL_TEXTURE_CUBE_MAP;
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

bool Texture::bindTexture()
{
	if (textureType != 4294967295) {
		glBindTexture(textureType, textureID);
		return true;
	}
	else {
		glBindTexture(textureType, 0);
		return false;
	}
}
