#include "Header.h"

void drawFloor(GLfloat x, GLfloat y, GLfloat z) {
	glColor4f(DGREY);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex3f(-x / 2.0, 0.0, -z);
	glVertex3f(x / 2.0, 0.0, -z);
	glVertex3f(-x / 2.0, 0.0, z - 3.0);

	glVertex3f(x / 2.0, 0.0, z - 3.0);
	glVertex3f(x / 2.0, 0.0, -z);
	glVertex3f(-x / 2.0, 0.0, z - 3.0);
	glEnd();
	glPopMatrix();
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
	glVertex3f(-x / 2.0, y + 5.0, -z / 2.0);
	glVertex3f(-x / 2.0, y + 5.0, z / 2.0);
	glVertex3f(-x / 2.0, y, -z / 2.0);

	glVertex3f(-x / 2.0, y, z / 2.0);
	glVertex3f(-x / 2.0, y + 5.0, z / 2.0);
	glVertex3f(-x / 2.0, y, -z / 2.0);

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

void drawLevel() {
	bool lockWindow = false;
	GLfloat glassHeight = 15.0 - 13.0;
	glBlendFunc(GL_ONE, GL_ZERO);
	drawFloor(15.0, 0.0, 20.0);
	drawCeiling(15.0, 15.0, 20.0);
	drawWalls(15.0, 15.0, 20.0);
	drawSpectator(15.0, 0.0, 20.0);
	drawTargetCovers(15.0, 2.0, 20.0);
	drawCover(15.0, 1.0, 20.0);
	drawTrapDoor(15.0, 0.0, 20.0);
	drawTrapRoom(15.0, 4.0, 20.0);
	drawGlass(15.0, glassHeight, 20.0);
}