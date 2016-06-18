#include "Header.h"
//STUFF

//Some global variables
extern bool lights_on = false;
GLint nLights = 0;
GLenum lights[] = { GL_LIGHT0 , GL_LIGHT1 , GL_LIGHT2 , GL_LIGHT3 , GL_LIGHT4 , GL_LIGHT5 , GL_LIGHT6 , GL_LIGHT7 };
GLfloat localAttCon = 1.0;
GLfloat localAttLin = 0.05;
GLfloat localAttQua = 0.0;


void createGroundLights() {

	GLfloat LightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightDiffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightDirection[] = { 0.0f, 0.5f, -1.0f };
	GLfloat cutoffv = 60.0f;
	GLfloat expv = 20.0f;


	//Ground lights
	GLfloat LightPosition[] = { 0.0f, 0.0f, 3.8f, 1.0f };
	glLightfv(lights[nLights], GL_POSITION, LightPosition);
	glLightfv(lights[nLights], GL_AMBIENT, LightAmbient);
	glLightfv(lights[nLights], GL_DIFFUSE, LightDiffuse);
	glLightfv(lights[nLights], GL_SPECULAR, LightSpecular);
	glLightfv(lights[nLights], GL_SPOT_DIRECTION, LightDirection);
	glLightf(lights[nLights], GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(lights[nLights], GL_LINEAR_ATTENUATION, localAttLin);
	glLightf(lights[nLights], GL_QUADRATIC_ATTENUATION, localAttQua);
	glLightf(lights[nLights], GL_SPOT_CUTOFF, cutoffv);
	glLightf(lights[nLights], GL_SPOT_EXPONENT, expv);
	glEnable(lights[nLights]);
	nLights++;
}



void createSpectatorLights() {
	
	GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightDirection[] = { 1.0f, -0.1f, 0.0f };
	GLfloat cutoffv = 90.0f;
	GLfloat expv = 30.0f;
	
	
	//Spectator STRONG Ceiling lights
	GLfloat LightPosition[] = { -9.0f, 13.0f, 10.0f, 1.0f };
	glLightfv(lights[nLights], GL_POSITION, LightPosition);
	glLightfv(lights[nLights], GL_AMBIENT, LightAmbient);
	glLightfv(lights[nLights], GL_DIFFUSE, LightDiffuse);
	glLightfv(lights[nLights], GL_SPECULAR, LightSpecular);
	glLightfv(lights[nLights], GL_SPOT_DIRECTION, LightDirection);
	glLightf(lights[nLights], GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(lights[nLights], GL_LINEAR_ATTENUATION, localAttLin);
	glLightf(lights[nLights], GL_QUADRATIC_ATTENUATION, localAttQua);
	glLightf(lights[nLights], GL_SPOT_CUTOFF, cutoffv);
	glLightf(lights[nLights], GL_SPOT_EXPONENT, expv);
	glEnable(lights[nLights]);
	nLights++;

	GLfloat LightPosition2[] = { -9.0f, 13.0f, 0.0f, 1.0f };
	glLightfv(lights[nLights], GL_POSITION, LightPosition2);
	glLightfv(lights[nLights], GL_AMBIENT, LightAmbient);
	glLightfv(lights[nLights], GL_DIFFUSE, LightDiffuse);
	glLightfv(lights[nLights], GL_SPECULAR, LightSpecular);
	glLightfv(lights[nLights], GL_SPOT_DIRECTION, LightDirection);
	glLightf(lights[nLights], GL_SPOT_CUTOFF, cutoffv);
	glLightf(lights[nLights], GL_SPOT_EXPONENT, expv);
	glLightf(lights[nLights], GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(lights[nLights], GL_LINEAR_ATTENUATION, localAttLin);
	glLightf(lights[nLights], GL_QUADRATIC_ATTENUATION, localAttQua);
	glEnable(lights[nLights]);
	nLights++;

	GLfloat LightPosition3[] = { -9.0f, 13.0f, -10.0f, 1.0f };
	glLightfv(lights[nLights], GL_POSITION, LightPosition3);
	glLightfv(lights[nLights], GL_AMBIENT, LightAmbient);
	glLightfv(lights[nLights], GL_DIFFUSE, LightDiffuse);
	glLightfv(lights[nLights], GL_SPECULAR, LightSpecular);
	glLightfv(lights[nLights], GL_SPOT_DIRECTION, LightDirection);
	glLightf(lights[nLights], GL_SPOT_CUTOFF, cutoffv);
	glLightf(lights[nLights], GL_SPOT_EXPONENT, expv);
	glLightf(lights[nLights], GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(lights[nLights], GL_LINEAR_ATTENUATION, localAttLin);
	glLightf(lights[nLights], GL_QUADRATIC_ATTENUATION, localAttQua);
	glEnable(lights[nLights]);
	nLights++;
}


void createCeilingLights() {
	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightDirection[] = { 0.0f, -1.0f, 0.0f };
	GLfloat cutoffv = 90.0f;
	GLfloat expv = 10.0f;
	

	for (int c = 0; c < 2; c++) {
		for (int r = 0; r < 2; r++){
			GLfloat rVal, cVal = 0.0;
			r ? rVal = -9.0 : rVal = 9.0;
			c ? cVal = -4.0 : cVal = 4.0;

			GLfloat LightPosition[] = { cVal, 15.0f, rVal, 1.0f };

			//Ceiling
			glLightfv(lights[nLights], GL_POSITION, LightPosition);
			glLightfv(lights[nLights], GL_AMBIENT, LightAmbient);
			glLightfv(lights[nLights], GL_DIFFUSE, LightDiffuse);
			glLightfv(lights[nLights], GL_SPECULAR, LightSpecular);
			glLightfv(lights[nLights], GL_SPOT_DIRECTION, LightDirection);
			glLightf(lights[nLights], GL_SPOT_CUTOFF, cutoffv);
			glLightf(lights[nLights], GL_SPOT_EXPONENT, expv);
			glLightf(lights[nLights], GL_CONSTANT_ATTENUATION, localAttCon);
			glLightf(lights[nLights], GL_LINEAR_ATTENUATION, localAttLin);
			glLightf(lights[nLights], GL_QUADRATIC_ATTENUATION, localAttQua);
			glEnable(lights[nLights]);
			nLights++;
		}
	}


}

void lightinit() {
	lights_on = true;

	GLfloat GlobalLightAmbient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_dif[] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat mat_shininess[] = { 50.0 };
	
	glEnable(GL_LIGHTING);
	//Change to local viewer
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	//Ambient
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalLightAmbient);
	//Let there be lights
	createCeilingLights();
	createSpectatorLights();
	createGroundLights();

	//Color Materials
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_dif);


}