
#include "Header.h"
#include <limits.h>

int frames = 0;
int drawSmallTargets = INT_MAX;
boolean passGlassGoingDown = false;
boolean gotBall = false;
GLboolean activatedBig = false;
GLboolean endingMod = false;
GLint endFrames = 0;
GLboolean fogToActivate = false;

GLboolean checkTargets(GLboolean *activeTargets) {
	for (int i = 0; i < 4; i++) {
		if (activeTargets[i])
			return true;
	}
	return false;
}


//Cientistas, Vidro, Bola, Targets pequenos, Target grande, Fog, end level 
void scripting(GLint *actions, GLboolean *activeTargets, irrklang::ISoundEngine* sEng, irrklang::ISoundSource** soundLib, int *timer) {
	
	frames++;

	if (actions[6] == 1 && endFrames > 170) {
		MessageBox(0, "Thanks for playing our game.\nHope to see you next time.", NULL, MB_OK);
		exit(0);
	}
	if (actions[6] == 2) {
		MessageBox(0, "Pity", NULL, MB_OK | MB_ICONSTOP);
		exit(0);
	}

	if (fogToActivate && endFrames > 80)
		actions[5] = 1;

	if (checkTargets(activeTargets)) {
		actions[3] = 1;
	}else if (actions[4] == 0) {
		timer[HIT] = 10;
		actions[3] = 2;
		actions[4] = 1;
	}else if (actions[4] == 3) {
		timer[DONT] = 10;
		actions[3] = 2;
		actions[4] = 4;

	}

	if (!activeTargets[4] &&
		(actions[4] == 1 || actions[4] == 4) &&
		!activatedBig) {
		activatedBig = true;
		activeTargets[4] = true;
	}

	if (!activeTargets[4] && activatedBig && actions[4] == 1) {
		actions[4] = 2;
		activatedBig = false;
	}

	if (actions[4] == 2) {
		activeTargets[0] = true;
		activeTargets[1] = true;
		activeTargets[2] = true;
		activeTargets[3] = true;
		actions[4] = 3;
	}

	if (actions[4] == 4)
		endFrames++;

	if (endFrames > 50 && activeTargets[4] && !fogToActivate) {
		fogToActivate = true;
		sEng->play2D(soundLib[8]);
	}
	if (endFrames > 50 && !activeTargets[4]) {
		actions[6] = 2;
	}

	if (frames == 1) {
		sEng->play2D(soundLib[0]);
		actions[1] = 1;
	}
	
	if (frames == 40)
		sEng->play2D(soundLib[1]);

	if (actions[1] == 0 && !passGlassGoingDown) {
		passGlassGoingDown = true;
	}

	if (actions[2] == 0 && passGlassGoingDown) {
		actions[2] = 1;
		gotBall = true;
	}
	if (actions[3] == 1 && gotBall) {
		actions[3] = 2;
	}

	if (actions[4] == 2 && actions[5] == 0) {
		actions[3] = 1;
	}

	if (actions[5] == 2)
		actions[6] = 2;
}