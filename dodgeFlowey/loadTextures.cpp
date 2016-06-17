#include "Header.h"
#include "light.h"
#include <iostream>
#include <map>

GLuint texture[128];
GLint texId = 0;
RgbImage imag;
std::map<std::string, GLint> textureIdMap;

void load_texture(std::string name) {
	glGenTextures(1, &texture[texId]);
	glBindTexture(GL_TEXTURE_2D, texture[texId]);
	if (!lights_on)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	std::string textureLocation = "resources/textures/" + name;
	const char * tl = textureLocation.c_str();
	imag.LoadBmpFile(tl);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imag.GetNumCols(), imag.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	textureIdMap.insert(std::pair<std::string, GLint>(name, texId));
	texId++;
}

GLuint getTexture(std::string name) {
	return texture[textureIdMap[name]];
}