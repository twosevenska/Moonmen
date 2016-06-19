#include "Header.h"
#include "light.h"
#include "level.h"
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



void createMaskedTextureObject(std::string maskName, std::string textureName, GLfloat* pos, GLfloat* dim, GLfloat rot, GLboolean boss) {
	
	if (lights_on)
		glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);									// Enable Blending
	//glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glBlendFunc(GL_DST_COLOR, GL_ZERO);				// Blend Screen Color With Zero (Black)
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2] -0.01);
	glRotatef(rot, 0.0, 0.0, 1.0);
	//glTranslatef(0.0, 5.0, 15.0);
	glTranslatef(-1.0, -1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, getTexture(maskName));

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(dim[0], 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(dim[0], dim[1], 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, dim[1], 0.0f);
	glEnd();

	glPopMatrix();

	if(boss)
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);					// Copy Image 2 Color To The Screen
	else
		glBlendFunc(GL_ONE, GL_ONE);

	glBindTexture(GL_TEXTURE_2D, getTexture(textureName));
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot, 0.0, 0.0, 1.0);
	//glTranslatef(0.0, 5.0, 15.0);
	glTranslatef(-1.0, -1.0, 0.0);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(dim[0], 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(dim[0], dim[1], 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, dim[1], 0.0f);
	glEnd();
	
	glPopMatrix();

	//glEnable(GL_DEPTH_TEST);							// Enable Depth Testing
	glDisable(GL_BLEND);								// Disable Blending
	glDisable(GL_TEXTURE_2D);

	if (lights_on)
		glEnable(GL_LIGHTING);
}