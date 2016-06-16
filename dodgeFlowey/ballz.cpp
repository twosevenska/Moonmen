#include <math.h>
#include "Header.h"
#include "level.h"

GLuint texture;
GLboolean textureLoaded = false;
RgbImage img;

GLfloat ball_radius = 0.3;
GLfloat ballSpeed = 0.1;

GLboolean moving = false;
GLboolean initialMove = false;

GLboolean calc_ball_look = false;
GLfloat vector_ball_look[3];

GLfloat distance_from_obs = 0.1f;/*in %*/
GLfloat line[3], ballP[3];

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

void getBallP(GLfloat *obs, GLfloat *lookAt) {
	GLfloat dist_look_orig = sqrt(lookAt[0] * lookAt[0] + lookAt[1] * lookAt[1] + lookAt[2] * lookAt[2]);

	distance_from_obs = 0.1 - 0.05*(log10(dist_look_orig + 5));

	printf("look-orig %f\n", dist_look_orig);
	printf("dist_obs %f\n", distance_from_obs);
	
	line[0] = lookAt[0] - obs[0];
	line[1] = lookAt[1] - obs[1];
	line[2] = lookAt[2] - obs[2];

	ballP[0] = obs[0] + (distance_from_obs * line[0]);
	ballP[1] = obs[1] + (distance_from_obs * line[1]);
	ballP[2] = obs[2] + (distance_from_obs * line[2]);

	
	ballP[0] += 1;
	ballP[1] += -1;
}

void initMovement(GLfloat *lookAt) {
	vector_ball_look[0] = lookAt[0] - ballP[0];
	vector_ball_look[1] = lookAt[1] - ballP[1];
	vector_ball_look[2] = lookAt[2] - ballP[2];
}

void getBallMovement(GLfloat *lookAt) {
	GLfloat dist_ball_look;

	dist_ball_look = sqrt(vector_ball_look[0] * vector_ball_look[0]
		+ vector_ball_look[1] * vector_ball_look[1]
		+ vector_ball_look[2] * vector_ball_look[2]);

	ballP[0] = ballP[0] + (ballSpeed * vector_ball_look[0]);
	ballP[1] = ballP[1] + (ballSpeed * vector_ball_look[1]);
	ballP[2] = ballP[2] + (ballSpeed * vector_ball_look[2]);
	
}

GLboolean drawBall(GLfloat *obs, GLfloat *lookAt, GLboolean moving) {
	/*
	if (!textureLoaded) {
		load("ballTexture.bmp");
		textureLoaded = true;
	}*/
	
	if (!moving) {
		getBallP(obs, lookAt);
		initialMove = false;
	}else {
		if (!initialMove) {
			initMovement(lookAt);
			getBallMovement(lookAt);
			initialMove = !initialMove;
		}
		else {
			getBallMovement(lookAt);
		}
	}
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	glTranslatef(ballP[0], ballP[1], ballP[2]);
	glutSolidSphere(ball_radius, 250, 250);
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
	return moving;
}