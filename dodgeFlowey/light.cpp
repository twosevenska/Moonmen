#include "Header.h"

//Some global variables
extern bool lights_on = false;

void lightinit() {
	lights_on = true;

	GLfloat localAttCon = 1.0;
	GLfloat localAttLin = 0.05;
	GLfloat localAttQua = 0.0;

	GLfloat GlobalLightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[] = { 0.0f, -1000.0f, 0.0f, 1.0f };

	glEnable(GL_LIGHTING);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//Ambiente
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalLightAmbient);
	//Tecto
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, localAttLin);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, localAttQua);
	glEnable(GL_LIGHT0);
}

void drawLightPos() {
	glColor4f(YELLOW);
	glPushMatrix();
	glTranslatef(0.0, 10.0, 0.0);
	glutSolidSphere(0.2, 250, 250);
	glPopMatrix();
}