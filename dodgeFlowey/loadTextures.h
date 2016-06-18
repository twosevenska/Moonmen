#pragma once
#include "Header.h"

void load_texture(std::string name);
GLuint getTexture(std::string name);
void createMaskedTextureObject(std::string maskName, std::string textureName, GLfloat x, GLfloat y, GLfloat z, GLfloat rot);