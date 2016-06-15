#include "Header.h"
#include "level.h"

GLuint textures[128];
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

void load(std::string name, GLint texId) {
	glGenTextures(1, &textures[texId]);
	glBindTexture(GL_TEXTURE_2D, textures[texId]);
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

void drawBall() {
	if (!textureLoaded) {
		load("ballTexture.bmp", 0);
		textureLoaded = true;
	}

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glPushMatrix();
	glTranslatef(ballx, bally, ballz);
	glutSolidSphere(0.2, 250, 250);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}