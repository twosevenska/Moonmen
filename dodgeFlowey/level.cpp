#include "Header.h"
#include "loadBlenderModels.h"

GLuint texture[128];
RgbImage imag;

void drawFloor(GLfloat x, GLfloat y, GLfloat z) {
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("resources/textures/floorTile.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x / 2.0, 0.0, z - 3.0);
	glTexCoord2f(4.0f, 4.0f); glVertex3f(x / 2.0, 0.0, -z);
	glTexCoord2f(0.0f, 4.0f); glVertex3f(-x / 2.0, 0.0, -z); 

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x / 2.0, 0.0, z - 3.0);
	glTexCoord2f(0.0f, 4.0f); glVertex3f(x / 2.0, 0.0, z - 3.0);
	glTexCoord2f(4.0f, 4.0f); glVertex3f(x / 2.0, 0.0, -z);
	
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawTrapDoor(GLfloat x, GLfloat y, GLfloat z) {
	glColor4f(DGREY);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, z - 3.0);
	glVertex3f(0.0, 0.0, z - 3.0);
	glVertex3f(-x / 2.0, 0.0, z);

	glVertex3f(0.0, 0.0, z);
	glVertex3f(0.0, 0.0, z - 3.0);
	glVertex3f(-x / 2.0, 0.0, z);

	glVertex3f(0.0, 0.0, z - 3.0);
	glVertex3f(x / 2.0, 0.0, z - 3.0);
	glVertex3f(0.0, 0.0, z);

	glVertex3f(x / 2.0, 0.0, z);
	glVertex3f(x / 2.0, 0.0, z - 3.0);
	glVertex3f(0.0, 0.0, z);
	glEnd();
	glPopMatrix();
}

void drawTrapRoom(GLfloat x, GLfloat y, GLfloat z) {
	//Back Wall
	glColor4f(BLACK);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, z - 3.0);
	glVertex3f(x / 2.0, 0.0, z - 3.0);
	glVertex3f(-x / 2.0, -y, z - 3.0);

	glVertex3f(x / 2.0, 0.0, z - 3.0);
	glVertex3f(-x / 2.0, -y, z - 3.0);
	glVertex3f(x / 2.0, -y, z - 3.0);
	glEnd();
	glPopMatrix();

	//Back Wall
	glColor4f(BLACK);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, z);
	glVertex3f(x / 2.0, 0.0, z);
	glVertex3f(-x / 2.0, -y, z);

	glVertex3f(x / 2.0, 0.0, z);
	glVertex3f(-x / 2.0, -y, z);
	glVertex3f(x / 2.0, -y, z);
	glEnd();
	glPopMatrix();

	//Bottom
	glColor4f(BLACK);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, -y, z - 3.0);
	glVertex3f(x / 2.0, -y, z - 3.0);
	glVertex3f(-x / 2.0, -y, z);

	glVertex3f(x / 2.0, -y, z - 3.0);
	glVertex3f(-x / 2.0, -y, z);
	glVertex3f(x / 2.0, -y, z);
	glEnd();
	glPopMatrix();

	//Side Walls
	glColor4f(BLACK);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, z - 3.0);
	glVertex3f(-x / 2.0, -y, z - 3.0);
	glVertex3f(-x / 2.0, 0.0, z);

	glVertex3f(-x / 2.0, -y, z - 3.0);
	glVertex3f(-x / 2.0, 0.0, z);
	glVertex3f(-x / 2.0, -y, z);

	glVertex3f(x / 2.0, 0.0, z - 3.0);
	glVertex3f(x / 2.0, -y, z - 3.0);
	glVertex3f(x / 2.0, 0.0, z);

	glVertex3f(x / 2.0, -y, z - 3.0);
	glVertex3f(x / 2.0, 0.0, z);
	glVertex3f(x / 2.0, -y, z);
	glEnd();
	glPopMatrix();
}

void drawCeiling(GLfloat x, GLfloat y, GLfloat z) {
	glColor4f(DGREY);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x, y, -z);
	glVertex3f(x / 2.0, y, -z);
	glVertex3f(-x, y, z);

	glVertex3f(x / 2.0, y, z);
	glVertex3f(x / 2.0, y, -z);
	glVertex3f(-x, y, z);

	glVertex3f(-x, y, -z / 2.0);
	glVertex3f(x / 2.0, y, -z / 2.0);
	glVertex3f(-x, y, z / 2.0);

	glVertex3f(x / 2.0, y, z / 2.0);
	glVertex3f(x / 2.0, y, -z / 2.0);
	glVertex3f(-x, y, z / 2.0);
	glEnd();
	glPopMatrix();
}

void drawWalls(GLfloat x, GLfloat y, GLfloat z) {
	//Left Wall
	glColor4f(LGREY);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, -z / 2.0);
	glVertex3f(-x / 2.0, 0.0, z / 2.0);
	glVertex3f(-x / 2.0, y - 5.0, -z / 2.0);

	glVertex3f(-x / 2.0, y - 5.0, z / 2.0);
	glVertex3f(-x / 2.0, 0.0, z / 2.0);
	glVertex3f(-x / 2.0, y - 5.0, -z / 2.0);

	glVertex3f(-x / 2.0, 0.0, -z);
	glVertex3f(-x / 2.0, 0.0, z);
	glVertex3f(-x / 2.0, y - 5.0, -z);

	glVertex3f(-x / 2.0, y - 5.0, z);
	glVertex3f(-x / 2.0, 0.0, z);
	glVertex3f(-x / 2.0, y - 5.0, -z);
	glEnd();
	glPopMatrix();

	//Right Wall
	glColor4f(LGREY);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(x / 2.0, 0.0, -z / 2.0);
	glVertex3f(x / 2.0, 0.0, z / 2.0);
	glVertex3f(x / 2.0, y, -z / 2.0);

	glVertex3f(x / 2.0, y, z / 2.0);
	glVertex3f(x / 2.0, 0.0, z / 2.0);
	glVertex3f(x / 2.0, y, -z / 2.0);

	glVertex3f(x / 2.0, 0.0, -z);
	glVertex3f(x / 2.0, 0.0, z);
	glVertex3f(x / 2.0, y, -z);

	glVertex3f(x / 2.0, y, z);
	glVertex3f(x / 2.0, 0.0, z);
	glVertex3f(x / 2.0, y, -z);
	glEnd();
	glPopMatrix();

	//Back Wall
	glColor4f(LGREY);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x, 0.0, -z);
	glVertex3f(x / 2.0, 0.0, -z);
	glVertex3f(x / 2.0, y, -z);

	glVertex3f(-x, 0.0, -z);
	glVertex3f(x / 2.0, y, -z);
	glVertex3f(-x, y, -z);
	glEnd();
	glPopMatrix();

	/*
	//Front Wall
	glColor4f(RED);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x, 0.0, z);
	glVertex3f(x / 2.0, 0.0, z);
	glVertex3f(x / 2.0, y, z);

	glVertex3f(-x, 0.0, z);
	glVertex3f(x / 2.0, y, z);
	glVertex3f(-x, y, z);
	glEnd();
	glPopMatrix();
	*/
}


void drawSpectatorFloor(GLfloat x, GLfloat y, GLfloat z) {
	glColor4f(DGREY);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x, 10.0, -z);
	glVertex3f(-x / 2.0, 10.0, -z);
	glVertex3f(-x, 10.0, z);

	glVertex3f(-x / 2.0, 10.0, z);
	glVertex3f(-x / 2.0, 10.0, -z);
	glVertex3f(-x, 10.0, z);

	glVertex3f(-x, 10.0, -z / 2.0);
	glVertex3f(-x / 2.0, 10.0, -z / 2.0);
	glVertex3f(-x, 10.0, z / 2.0);

	glVertex3f(-x / 2.0, 10.0, z / 2.0);
	glVertex3f(-x / 2.0, 10.0, -z / 2.0);
	glVertex3f(-x, 10.0, z / 2.0);
	glEnd();
	glPopMatrix();
}

void drawSpectator(GLfloat x, GLfloat y, GLfloat z) {
	drawSpectatorFloor(x, y, z);

	y = 10.0;

	//Left Wall
	glColor4f(LGREY);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x, y + 5.0, -z / 2.0);
	glVertex3f(-x, y + 5.0, z / 2.0);
	glVertex3f(-x, y, -z / 2.0);

	glVertex3f(-x, y, z / 2.0);
	glVertex3f(-x, y + 5.0, z / 2.0);
	glVertex3f(-x, y, -z / 2.0);

	glVertex3f(-x, y + 5.0, -z);
	glVertex3f(-x, y + 5.0, z);
	glVertex3f(-x, y, -z);

	glVertex3f(-x, y, z);
	glVertex3f(-x, y + 5.0, z);
	glVertex3f(-x, y, -z);
	glEnd();
	glPopMatrix();

	//Glass
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(HGLASS);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, y + 5.0, -z);
	glVertex3f(-x / 2.0, y + 5.0, z);
	glVertex3f(-x / 2.0, y, -z);

	glVertex3f(-x / 2.0, y, z);
	glVertex3f(-x / 2.0, y + 5.0, z);
	glVertex3f(-x / 2.0, y, -z);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

void drawTargetCovers(GLfloat x, GLfloat y, GLfloat z) {
	//Front Wall
	glColor4f(RED);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, z - 8.0);
	glVertex3f(0.0, 0.0, z - 8.0);
	glVertex3f(0.0, y, z - 8.0);

	glVertex3f(-x / 2.0, 0.0, z - 8.0);
	glVertex3f(0.0, y, z - 8.0);
	glVertex3f(-x / 2.0, y, z - 8.0);
	glEnd();
	glPopMatrix();

	glColor4f(RED);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 4.0, 0.0, 0.0);
	glVertex3f(x / 4.0, 0.0, 0.0);
	glVertex3f(x / 4.0, y, 0.0);

	glVertex3f(-x / 4.0, 0.0, 0.0);
	glVertex3f(x / 4.0, y, 0.0);
	glVertex3f(-x / 4.0, y, 0.0);
	glEnd();
	glPopMatrix();

	glColor4f(RED);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, -z + 8.0);
	glVertex3f(x / 2.0, 0.0, -z + 8.0);
	glVertex3f(x / 2.0, y, -z + 8.0);

	glVertex3f(0.0, 0.0, -z + 8.0);
	glVertex3f(x / 2.0, y, -z + 8.0);
	glVertex3f(0.0, y, -z + 8.0);
	glEnd();
	glPopMatrix();

	//Back Wall
	glColor4f(BLUE);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, z - 9.0);
	glVertex3f(0.0, 0.0, z - 9.0);
	glVertex3f(0.0, y, z - 9.0);

	glVertex3f(-x / 2.0, 0.0, z - 9.0);
	glVertex3f(0.0, y, z - 9.0);
	glVertex3f(-x / 2.0, y, z - 9.0);
	glEnd();
	glPopMatrix();

	glColor4f(BLUE);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 4.0, 0.0, -1.0);
	glVertex3f(x / 4.0, 0.0, -1.0);
	glVertex3f(x / 4.0, y, -1.0);

	glVertex3f(-x / 4.0, 0.0, -1.0);
	glVertex3f(x / 4.0, y, -1.0);
	glVertex3f(-x / 4.0, y, -1.0);
	glEnd();
	glPopMatrix();

	glColor4f(BLUE);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, -z + 7.0);
	glVertex3f(x / 2.0, 0.0, -z + 7.0);
	glVertex3f(x / 2.0, y, -z + 7.0);

	glVertex3f(0.0, 0.0, -z + 7.0);
	glVertex3f(x / 2.0, y, -z + 7.0);
	glVertex3f(0.0, y, -z + 7.0);
	glEnd();
	glPopMatrix();

	//Top
	glColor4f(GREEN);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, y, z - 8.0);
	glVertex3f(0.0, y, z - 8.0);
	glVertex3f(-x / 2.0, y, z - 9.0);

	glVertex3f(0.0, y, z - 9.0);
	glVertex3f(0.0, y, z - 8.0);
	glVertex3f(-x / 2.0, y, z - 9.0);

	glVertex3f(-x / 2.0, y, z - 8.0);
	glVertex3f(0.0, y, z - 8.0);
	glVertex3f(-x / 2.0, y, z - 8.0);

	glVertex3f(0.0, y, z - 9.0);
	glVertex3f(0.0, y, z - 8.0);
	glVertex3f(-x / 2.0, y, z - 9.0);
	glEnd();
	glPopMatrix();

	glColor4f(GREEN);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 4.0, y, 0.0);
	glVertex3f(x / 4.0, y, 0.0);
	glVertex3f(-x / 4.0, y, -1.0);

	glVertex3f(x / 4.0, y, -1.0);
	glVertex3f(x / 4.0, y, 0.0);
	glVertex3f(-x / 4.0, y, -1.0);

	glVertex3f(-x / 4.0, y, 0.0);
	glVertex3f(x / 4.0, y, 0.0);
	glVertex3f(-x / 4.0, y, 0.0);

	glVertex3f(x / 4.0, y, -1.0);
	glVertex3f(x / 4.0, y, 0.0);
	glVertex3f(-x / 4.0, y, -1.0);
	glEnd();
	glPopMatrix();

	glColor4f(GREEN);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(x / 2.0, y, -z + 7.0);
	glVertex3f(0.0, y, -z + 7.0);
	glVertex3f(x / 2.0, y, -z + 8.0);

	glVertex3f(0.0, y, -z + 8.0);
	glVertex3f(0.0, y, -z + 7.0);
	glVertex3f(x / 2.0, y, -z + 8.0);

	glVertex3f(x / 2.0, y, -z + 7.0);
	glVertex3f(0.0, y, -z + 7.0);
	glVertex3f(x / 2.0, y, -z + 7.0);

	glVertex3f(0.0, y, -z + 8.0);
	glVertex3f(0.0, y, -z + 7.0);
	glVertex3f(x / 2.0, y, -z + 8.0);
	glEnd();
	glPopMatrix();

	//Right Wall
	glColor4f(YELLOW);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, z - 8.0);
	glVertex3f(0.0, 0.0, z - 9.0);
	glVertex3f(0.0, y, z - 8.0);

	glVertex3f(0.0, y, z - 9.0);
	glVertex3f(0.0, 0.0, z - 9.0);
	glVertex3f(0.0, y, z - 8.0);

	glVertex3f(0.0, 0.0, z - 8.0);
	glVertex3f(0.0, 0.0, z - 9.0);
	glVertex3f(0.0, y, z - 8.0);

	glVertex3f(0.0, y, z - 9.0);
	glVertex3f(0.0, 0.0, z - 9.0);
	glVertex3f(0.0, y, z - 8.0);
	glEnd();
	glPopMatrix();

	glColor4f(YELLOW);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(x / 4.0, 0.0, 0.0);
	glVertex3f(x / 4.0, 0.0, -1.0);
	glVertex3f(x / 4.0, y, 0.0);

	glVertex3f(x / 4.0, y, -1.0);
	glVertex3f(x / 4.0, 0.0, -1.0);
	glVertex3f(x / 4.0, y, 0.0);

	glVertex3f(x / 4.0, 0.0, 0.0);
	glVertex3f(x / 4.0, 0.0, -1.0);
	glVertex3f(x / 4.0, y, 0.0);

	glVertex3f(x / 4.0, y, -1.0);
	glVertex3f(x / 4.0, 0.0, -1.0);
	glVertex3f(x / 4.0, y, 0.0);
	glEnd();
	glPopMatrix();

	//Left Wall

	glColor4f(YELLOW);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 4.0, 0.0, 0.0);
	glVertex3f(-x / 4.0, 0.0, -1.0);
	glVertex3f(-x / 4.0, y, 0.0);

	glVertex3f(-x / 4.0, y, -1.0);
	glVertex3f(-x / 4.0, 0.0, -1.0);
	glVertex3f(-x / 4.0, y, 0.0);

	glVertex3f(-x / 4.0, 0.0, 0.0);
	glVertex3f(-x / 4.0, 0.0, -1.0);
	glVertex3f(-x / 4.0, y, 0.0);

	glVertex3f(-x / 4.0, y, -1.0);
	glVertex3f(-x / 4.0, 0.0, -1.0);
	glVertex3f(-x / 4.0, y, 0.0);
	glEnd();
	glPopMatrix();


	glColor4f(YELLOW);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, -z + 7.0);
	glVertex3f(0.0, 0.0, -z + 8.0);
	glVertex3f(0.0, y, -z + 7.0);

	glVertex3f(0.0, y, -z + 8.0);
	glVertex3f(0.0, 0.0, -z + 8.0);
	glVertex3f(0.0, y, -z + 7.0);

	glVertex3f(0.0, 0.0, -z + 7.0);
	glVertex3f(0.0, 0.0, -z + 8.0);
	glVertex3f(0.0, y, -z + 7.0);

	glVertex3f(0.0, y, -z + 8.0);
	glVertex3f(0.0, 0.0, -z + 8.0);
	glVertex3f(0.0, y, -z + 7.0);
	glEnd();
	glPopMatrix();
}

void drawCover(GLfloat x, GLfloat y, GLfloat z) {

	//Front Wall
	glColor4f(RED);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, z - 3.0);
	glVertex3f(x / 2.0, 0.0, z - 3.0);
	glVertex3f(x / 2.0, y, z - 3.0);

	glVertex3f(-x / 2.0, 0.0, z - 3.0);
	glVertex3f(x / 2.0, y, z - 3.0);
	glVertex3f(-x / 2.0, y, z - 3.0);
	glEnd();
	glPopMatrix();

	//Back Wall
	glColor4f(BLUE);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, z - 3.2);
	glVertex3f(x / 2.0, 0.0, z - 3.2);
	glVertex3f(x / 2.0, y, z - 3.2);

	glVertex3f(-x / 2.0, 0.0, z - 3.2);
	glVertex3f(x / 2.0, y, z - 3.2);
	glVertex3f(-x / 2.0, y, z - 3.2);
	glEnd();
	glPopMatrix();

	//Top
	glColor4f(GREEN);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, y, z - 3.0);
	glVertex3f(x / 2.0, y, z - 3.0);
	glVertex3f(-x / 2.0, y, z - 3.2);

	glVertex3f(x / 2.0, y, z - 3.2);
	glVertex3f(x / 2.0, y, z - 3.0);
	glVertex3f(-x / 2.0, y, z - 3.2);

	glVertex3f(-x / 2.0, y, z - 3.0);
	glVertex3f(x / 2.0, y, z - 3.0);
	glVertex3f(-x / 2.0, y, z - 3.0);

	glVertex3f(x / 2.0, y, z - 3.2);
	glVertex3f(x / 2.0, y, z - 3.0);
	glVertex3f(-x / 2.0, y, z - 3.2);
	glEnd();
	glPopMatrix();
}

void drawGlass(GLfloat x, GLfloat y, GLfloat z) {
	//Glass
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(CGLASS);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, z - 3.1);
	glVertex3f(x / 2.0, 0.0, z - 3.1);
	glVertex3f(x / 2.0, y, z - 3.1);

	glVertex3f(-x / 2.0, 0.0, z - 3.1);
	glVertex3f(x / 2.0, y, z - 3.1);
	glVertex3f(-x / 2.0, y, z - 3.1);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

void drawLightPos() {
	glPushMatrix();
	//glEnable(GL_COLOR_MATERIAL);
	//glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 10, 0);
	glVertex3i(0, 12, 0);
	glEnd();
	//glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}


void drawLevel() {
	
	bool lockWindow = false;
	GLfloat glassHeight = 15.0 - 13.0;
	glBlendFunc(GL_ONE, GL_ZERO);
	//drawmodel();
	drawFloor(15.0, 0.0, 20.0);
	drawCeiling(15.0, 15.0, 20.0);
	drawWalls(15.0, 15.0, 20.0);
	drawSpectator(15.0, 0.0, 20.0);
	drawTargetCovers(15.0, 2.0, 20.0);
	drawCover(15.0, 1.0, 20.0);
	drawTrapDoor(15.0, 0.0, 20.0);
	drawTrapRoom(15.0, 4.0, 20.0);
	drawGlass(15.0, glassHeight, 20.0);
	//drawLightPos();
}