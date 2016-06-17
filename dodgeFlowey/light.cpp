#include "Header.h"

//Some global variables
extern bool lights_on = false;
GLint nLights = 0;
GLenum lights[] = { GL_LIGHT0 , GL_LIGHT1 , GL_LIGHT2 , GL_LIGHT3 , GL_LIGHT4 , GL_LIGHT5 , GL_LIGHT6 , GL_LIGHT7 };
GLfloat lightsPos[7][4] = {};
GLfloat localAttCon = 1.0;
GLfloat localAttLin = 0.05;
GLfloat localAttQua = 0.0;

void setLightPos(GLfloat x, GLfloat y, GLfloat z, GLfloat type, GLint light) {
	lightsPos[light][0] = x;
	lightsPos[light][1] = y;
	lightsPos[light][2] = z;
	lightsPos[light][3] = type;
}

void reloadLightPos() {
	for (int i = 0; i < nLights; i++) {
		glLightfv(lights[nLights], GL_POSITION, lightsPos[i]);
	}
}

void createSpectatorLights() {
	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDirection[] = { 1.0f, -1.0f, 0.0f, 0.0f};
	GLfloat LightSpecular[] = { 0.4f, 0.4f, 0.4f, 1.0f };

	GLfloat LightPosition[] = { -18.0f, 15.0f, 10.0f, 0.0f };
	//Spectator STRONG Ceiling lights
	glLightfv(lights[nLights], GL_POSITION, LightPosition);
	glLightfv(lights[nLights], GL_AMBIENT, LightAmbient);
	glLightfv(lights[nLights], GL_DIFFUSE, LightDiffuse);
	glLightfv(lights[nLights], GL_SPECULAR, LightSpecular);
	glLightfv(lights[nLights], GL_SPOT_DIRECTION, LightDirection);
	glLightf(lights[nLights], GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(lights[nLights], GL_LINEAR_ATTENUATION, localAttLin);
	glLightf(lights[nLights], GL_QUADRATIC_ATTENUATION, localAttQua);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.f);
	glEnable(lights[nLights]);
	nLights++;

	GLfloat LightPosition2[] = { -18.0f, 15.0f, -10.0f, 0.0f };
	glLightfv(lights[nLights], GL_POSITION, LightPosition2);
	glLightfv(lights[nLights], GL_AMBIENT, LightAmbient);
	glLightfv(lights[nLights], GL_DIFFUSE, LightDiffuse);
	glLightfv(lights[nLights], GL_SPECULAR, LightSpecular);
	glLightfv(lights[nLights], GL_SPOT_DIRECTION, LightDirection);
	glLightf(lights[nLights], GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(lights[nLights], GL_LINEAR_ATTENUATION, localAttLin);
	glLightf(lights[nLights], GL_QUADRATIC_ATTENUATION, localAttQua);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.f);
	glEnable(lights[nLights]);
	nLights++;
}


void createCeilingLights() {
	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightDirection[] = { 0.0f, -1.0f, 0.0f, 0.0f };

	for (int c = 0; c < 2; c++) {
		for (int r = 0; r < 2; r++){
			GLfloat rVal, cVal = 0.0;
			r ? rVal = -10.0 : rVal = 10.0;
			c ? cVal = -6.0 : cVal = 6.0;

			GLfloat LightPosition[] = { cVal, 16.0f, rVal, 1.0f };

			//Ceiling
			glLightfv(lights[nLights], GL_POSITION, LightPosition);
			glLightfv(lights[nLights], GL_AMBIENT, LightAmbient);
			glLightfv(lights[nLights], GL_DIFFUSE, LightDiffuse);
			glLightfv(lights[nLights], GL_SPECULAR, LightSpecular);
			glLightfv(lights[nLights], GL_SPOT_DIRECTION, LightDirection);
			glLightf(lights[nLights], GL_CONSTANT_ATTENUATION, localAttCon);
			glLightf(lights[nLights], GL_LINEAR_ATTENUATION, localAttLin);
			glLightf(lights[nLights], GL_QUADRATIC_ATTENUATION, localAttQua);
			glEnable(lights[nLights]);
			nLights++;

			//drawLightPos(cVal, 10.0, rVal);
		}
	}
}

void lightinit() {
	lights_on = true;

	GLfloat GlobalLightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	glEnable(GL_LIGHTING);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//Ambient
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalLightAmbient);
	//Create remaining lights
	createCeilingLights();
	createSpectatorLights();
}