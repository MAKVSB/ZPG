#pragma once

#include "GlobalInclude.h"
#include <string>
#include <vector>

#include <IL/il.h>
//#include <IL/ilu.h>
//#include <IL/ilut.h>
class Texture {
private:
	GLuint textureID = -1;
	GLenum textureType = -1;
	void loadCubeMapFace(GLenum target, std::string path);
public:
	void loadTexture2D(std::string path);
	void createCubeMap(std::vector<std::string> faces, std::string basePath = "");
	void bindTexture();
};