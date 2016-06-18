
#include "Header.h"
#include <limits.h>

int frames = 0;
int drawSmallTargets = INT_MAX;
boolean passGlassGoingDown = false;
boolean gotBall = false;

//Cientistas, Vidro, Bola, Targets pequenos, Target grande, Fog, end level 
void scripting(GLint *actions) {
	
	
	frames++;

	if(frames == 1)
		actions[1] = 1;
	
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
}