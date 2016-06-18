
#include "Header.h"

GLint frames = 0;

//Cientistas, Vidro, Bola, Targets pequenos, Target grande, Fog, end level 
void scripting(GLint *actions) {
	frames++;

	if (frames > 0 && frames < 10) {
		actions[1] = 1;
	}
	if (actions[1] == 0 && frames > 50) {
		actions[2] = 1;
		if(frames > 70)
			actions[3] = 1;
	}
}