#include "Header.h"
#include "level.h"

GLuint texture;
GLboolean textureLoaded = false;
RgbImage img;

GLfloat ball_radius = 1.0;
GLfloat ballx = 1.0;
GLfloat bally = 4.0;
GLfloat ballz = 16.0;

GLfloat xSpeed = 0.2f;
GLfloat ySpeed = 0.07f;

void animate() {
	if (ballx > 0.0001)
		ballx += xSpeed;
	else
		xSpeed = -xSpeed;

	if (bally > 0.0001)
		bally += ySpeed;
	else
		ySpeed = -ySpeed;

}

void load(std::string name) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	std::string textureLocation = "resources/textures/" + name;
	const char * tl = textureLocation.c_str();
	img.LoadBmpFile(tl);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img.GetNumCols(), img.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, img.ImageData());
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());
}

void drawBall(GLfloat *obsP, GLfloat *lookP) {
	if (!textureLoaded) {
		load("ballTexture.bmp");
		textureLoaded = true;
	}

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	glTranslatef(obsP[0], obsP[1], obsP[2] - 1.0f);
	glutSolidSphere(0.2, 250, 250);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}