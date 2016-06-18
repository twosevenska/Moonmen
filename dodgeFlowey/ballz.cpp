#include <math.h>
#include "Header.h"
#include "level.h"

GLuint texture;
GLboolean textureLoaded = false;
RgbImage img;

GLfloat ballRadius = 0.5f;
GLfloat ballSpeed = 0.05f;
GLfloat ydelta;
GLfloat ydelta_inc;

GLboolean moving = false;
GLboolean initialMove = false;

GLfloat vector_ball_look[3];
GLfloat midP_ball_look[3];


GLfloat distance_from_obs = 0.1f;/*in %*/
GLfloat line[3], ballP[3];

GLfloat * getBallPosition() {
	return ballP;
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

void getBallP(GLfloat *obs, GLfloat *lookAt) {
	GLfloat dist_look_orig = sqrt(lookAt[0] * lookAt[0] + lookAt[1] * lookAt[1] + lookAt[2] * lookAt[2]);

	distance_from_obs = 0.1 - 0.05*(log10(dist_look_orig + 5));
	
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

	midP_ball_look[0] = ballP[0] + 0.5*vector_ball_look[0];
	midP_ball_look[1] = ballP[1] + 0.5*vector_ball_look[1];
	midP_ball_look[2] = ballP[2] + 0.5*vector_ball_look[2];

	ballSpeed = abs(ballSpeed);
	ydelta = 0.1f;
	ydelta_inc = 0.05f;
}

GLint getBallMovement(GLfloat *lookAt, GLboolean *targets) {
	GLfloat dist_ball_look;
	
	dist_ball_look = sqrt(vector_ball_look[0] * vector_ball_look[0]
		+ vector_ball_look[1] * vector_ball_look[1]
		+ vector_ball_look[2] * vector_ball_look[2]);

	//Collisions
	//1st target frontface
	if (targets[0] &&
		((ballP[0] - ballRadius > -7.0	&& ballP[0] - ballRadius < -5.0) ||
			(ballP[0] + ballRadius > -7.0	&& ballP[0] + ballRadius < -5.0)) &&
		ballP[1] + ballRadius > 2.2		&& ballP[1] + ballRadius < 4.7 &&
		ballP[2] - ballRadius > 9.4		&& ballP[2] - ballRadius < 10.0) {
		targets[0] = false;
		return false;
	}
	//1st target backface
	if (targets[0] &&
		((ballP[0] - ballRadius > -7.0	&& ballP[0] - ballRadius < -5.0) ||
			(ballP[0] + ballRadius > -7.0	&& ballP[0] + ballRadius < -5.0)) &&
		ballP[1] + ballRadius > 2.2		&& ballP[1] + ballRadius < 4.7 &&
		ballP[2] + ballRadius > 9.4		&& ballP[2] + ballRadius < 10.0) {
		targets[0] = false;
		return false;
	}
	//2nd target frontface
	if (targets[1] &&
		((ballP[0] - ballRadius > -3.0	&& ballP[0] - ballRadius < -1.0) ||
			(ballP[0] + ballRadius > -3.0	&& ballP[0] + ballRadius < -1.0)) &&
		ballP[1] - ballRadius > 2.2		&& ballP[1] + ballRadius < 4.7 &&
		ballP[2] - ballRadius > 9.5		&& ballP[2] - ballRadius < 10.1) {
		targets[1] = false;
		return false;
	}
	//2nd target backface
	if (targets[1] &&
		((ballP[0] - ballRadius > -3.0	&& ballP[0] - ballRadius < -1.0) ||
			(ballP[0] + ballRadius > -3.0	&& ballP[0] + ballRadius < -1.0)) &&
		ballP[1] - ballRadius > 2.2		&& ballP[1] + ballRadius < 4.7 &&
		ballP[2] + ballRadius > 9.5		&& ballP[2] + ballRadius < 10.1) {
		targets[1] = false;
		return false;
	}
	//3rd target frontface
	if (targets[2] &&
		((ballP[0] - ballRadius > 1.0	&& ballP[0] - ballRadius < 3.0) ||
			(ballP[0] + ballRadius > 1.0	&& ballP[0] + ballRadius < 3.0)) &&
		ballP[1] - ballRadius > 2.2		&& ballP[1] + ballRadius < 4.7 &&
		ballP[2] - ballRadius > -16.2	&& ballP[2] - ballRadius < -15.4) {
		targets[2] = false;
		return false;
	}
	//3rd target backface
	if (targets[2] &&
		((ballP[0] - ballRadius > 1.0	&& ballP[0] - ballRadius < 3.0) ||
			(ballP[0] + ballRadius > 1.0	&& ballP[0] + ballRadius < 3.0)) &&
		ballP[1] - ballRadius > 2.2		&& ballP[1] + ballRadius < 4.7 &&
		ballP[2] + ballRadius > -16.2	&& ballP[2] + ballRadius < -15.4) {
		targets[2] = false;
		return false;
	}
	//4th target frontface
	if (targets[3] &&
		((ballP[0] - ballRadius > 5.0	&& ballP[0] - ballRadius < 7.0) ||
		(ballP[0] + ballRadius > 5.0	&& ballP[0] + ballRadius < 7.0)) &&
		ballP[1] - ballRadius > 2.2		&& ballP[1] + ballRadius < 4.7 &&
		ballP[2] - ballRadius > -16.2	&& ballP[2] - ballRadius < -15.4) {
		targets[3] = false;
		return false;
	}
	//4th target backface
	if (targets[3] &&
		((ballP[0] - ballRadius > 5.0	&& ballP[0] - ballRadius < 7.0) ||
		(ballP[0] + ballRadius > 5.0	&& ballP[0] + ballRadius < 7.0)) &&
		ballP[1] - ballRadius > 2.2		&& ballP[1] + ballRadius < 4.7 &&
		ballP[2] + ballRadius > -16.2	&& ballP[2] + ballRadius < -15.4) {
		targets[3] = false;
		return false;
	}


	ballP[0] += (ballSpeed * vector_ball_look[0]);
	ballP[1] += (ballSpeed * vector_ball_look[1]) - ydelta;
	ballP[2] += (ballSpeed * vector_ball_look[2]);

	//First black border
	if (ballP[1] - ballRadius < 2.0 &&
		(ballP[2] - ballRadius < 14.5	&& ballP[2] - ballRadius > 13.5 ||
		ballP[2] + ballRadius < 14.5	&& ballP[2] + ballRadius > 13.5) ||
		//Nearest block front
		(ballP[0] - ballRadius > -8.0	&& ballP[0] - ballRadius < 0.0 &&
		ballP[1] - ballRadius < 2.0		&&
		ballP[2] - ballRadius > 9.1		&& ballP[2] - ballRadius < 10.9) ||
		//Nearest block back
		(ballP[0] - ballRadius > -8.0	&& ballP[0] - ballRadius < 0.0 &&
		ballP[1] - ballRadius < 2.0		&&
		ballP[2] + ballRadius > 9.1		&& ballP[2] + ballRadius < 10.9) ||
		
		//Middle block front
		(ballP[0] - ballRadius > -4.0	&& ballP[0] - ballRadius < 4.0 &&
		ballP[1] - ballRadius < 2.0		&&
		ballP[2] - ballRadius > -0.9	&& ballP[2] - ballRadius < 0.9) ||
		//Middle block back
		(ballP[0] - ballRadius > -4.0	&& ballP[0] - ballRadius < 4.0 &&
		ballP[1] - ballRadius < 2.0		&&
		ballP[2] + ballRadius > -0.9	&& ballP[2] + ballRadius < 0.9) ||

		//Farest block front
		(ballP[0] + ballRadius > 0.0	&& ballP[0] + ballRadius < 8.0 &&
		ballP[1] - ballRadius < 2.0		&&
		ballP[2] - ballRadius < -15.1	&& ballP[2] - ballRadius > -16.9) ||
		//Farest block back
		(ballP[0] + ballRadius > 0.0	&& ballP[0] + ballRadius < 8.0 &&
		ballP[1] - ballRadius < 2.0		&&
		ballP[2] + ballRadius < -15.1	&& ballP[2] + ballRadius > -16.9)
		) return false;

	//bounce
	//back wall
	if (ballP[2] - ballRadius < -20.0) {
		ballP[2] = -20.0 + ballRadius;
		ballSpeed *= -1;

		if (vector_ball_look[1] > 0.0) {
			vector_ball_look[1] *= -1;
		}
		else {
			if (ydelta < 0.0) {
				vector_ball_look[1] *= -1;
				ydelta *= -1;
			}
			if (ydelta_inc < 0.0)
				ydelta_inc *= -1;
		}
	}

	//floor
	if (ballP[1] - ballRadius < 0.0) {
		ballP[1] = ballRadius;
		ydelta *= -1;
		if (vector_ball_look[1] < 0.0) {
			vector_ball_look[1] *= -1;
		}else {
			if (ydelta_inc < 0.0) {
				vector_ball_look[1] *= -1;
				ydelta_inc *= -1;
			}
		}
	}

	//ceiling
	if (ballP[1] + ballRadius > 16.000001) {
		ballP[1] = 16.0 - ballRadius;
		ydelta *= -1;
		if(vector_ball_look[1] < 0.0)
			vector_ball_look[1] *= -1;
		/*
		printf("__________\ny %f\nspeed %f\ndelta %f\ninc %f\n",
			ballP[1],ballSpeed, ydelta, ydelta_inc);
		*/
	}
	/*
	printf("___________\nx %.3f + %.3f = %.3f\ny %.3f + %.3f = %.3f\nz %.3f + %.3f = %.3f\n",
		ballP[0], ballRadius, ballP[0] + ballRadius,
		ballP[1], ballRadius, ballP[1] + ballRadius,
		ballP[2], ballRadius, ballP[2] + ballRadius);
	*/
	if (ballP[0] - ballRadius < -8.0 || ballP[0] + ballRadius > 8.0 || ballP[2] > 20)
		return false;

	ydelta += ydelta_inc;
	return true;
}

GLboolean drawBall(GLfloat *obs, GLfloat *lookAt, GLboolean moving, GLboolean *targets) {
	
	if (!textureLoaded) {
		load("ballTexture.bmp");
		textureLoaded = true;
	}
	
	if (!moving) {
		getBallP(obs, lookAt);
		initialMove = false;
	}else {
		if (!initialMove) {
			initMovement(lookAt);
			moving = getBallMovement(lookAt, targets);
			initialMove = !initialMove;
		}
		else {
			moving = getBallMovement(lookAt, targets);
		}
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	GLUquadricObj* s = gluNewQuadric();
	gluQuadricDrawStyle(s, GLU_FILL);
	gluQuadricNormals(s, GLU_SMOOTH);
	gluQuadricTexture(s, GL_TRUE);
	glTranslatef(ballP[0], ballP[1], ballP[2]);
	gluSphere(s, ballRadius, 250, 250);
	gluDeleteQuadric(s);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	/*glPushMatrix();
	glTranslatef(lookAt[0], lookAt[1], lookAt[2]);
	glutSolidSphere(ballRadius, 250, 250);
	glPopMatrix();*/
	return moving;
}