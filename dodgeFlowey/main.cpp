//For windows
//#include <windows.h>
#include <math.h>
#include "Header.h"
#include "level.h"
#include "light.h"
#include "ballz.h"
#include "script.h"
#include "text.h"


//Dev flags
GLboolean god = false;
GLboolean drawAxis = true;
GLboolean textureDevMode = false;

//Sounds
irrklang::ISoundEngine* soundEngine;
irrklang::ISound* backgroundSound;
irrklang::ISoundSource* soundLib[20];
GLboolean firstTargetHit = false;
GLboolean firstRound = true;

//Coordinate system variables
GLfloat   xC = 70.0, yC = 70.0, zC = 70.0;
GLint     wScreen = 800, hScreen = 600;

//Observer Stuff
GLint    defineView = 0;
GLint    defineProj = 1;
GLfloat  raio = 20;
GLfloat  angulo = 0.5*PI;
GLfloat  obsP[] = { 0, 5, 18};
GLfloat  incy = 1;
GLfloat  inca = 1;

GLfloat  lookP[] = { 0, 0, 0};
GLfloat  rayVision = 45;
GLfloat  limitsLookP[] = { -rayVision, rayVision };

GLfloat  posLimit = 6.5;
GLfloat  limitsWalkP[] = { -posLimit + 1, posLimit - 1 };

//Ball Movement
GLboolean ballMoving = false;

//Targeting
GLboolean activeTargets[5] = { true, true, true, true, false};
GLboolean checkTargets[5] = { true, true, true, true, false };

//Scripting		
//Scientists, Glass, Ball, Small Targets, Big Target, Fog, EndLevel 		
GLint actions[7] = { 0, 0, 0, 0, 0, 0, 0 };

//2D stuff
char *text[] = { "","HELLO.","HIT!","TRUST ME!", "DON'T!"};
int timer[] = { 0,0,0,0,0 };

//Time is a woobly thing
GLint    repete = 2;
GLfloat  rr = 1;
GLint    maxR = 20;
GLint    numFrames = 60;              //numero de imagens a colocar em loop na tela
GLint    msec = 80;					//.. definicao do timer (actualizacao)


void soundLoad(){
	//Sound Engine
	soundEngine = irrklang::createIrrKlangDevice();

	//Start the background music
	backgroundSound = soundEngine->play2D("resources/sounds/backgroundSound.mp3", true, false, true);
	backgroundSound->setVolume(0.2f);

	soundLib[0] = soundEngine->addSoundSourceFromFile("resources/sounds/0-Greetings.mp3");
	soundLib[1] = soundEngine->addSoundSourceFromFile("resources/sounds/1-ThrowPreparation.mp3");
	soundLib[2] = soundEngine->addSoundSourceFromFile("resources/sounds/2-Throw.mp3");
	soundLib[3] = soundEngine->addSoundSourceFromFile("resources/sounds/3-FirstTarget.mp3");
	soundLib[4] = soundEngine->addSoundSourceFromFile("resources/sounds/4-SmallTargetShatters.mp3");
	soundLib[4]->setDefaultVolume(0.3f);
	soundLib[5] = soundEngine->addSoundSourceFromFile("resources/sounds/5-BigTargetShatters.mp3");
	soundLib[5]->setDefaultVolume(0.3f);
	soundLib[6] = soundEngine->addSoundSourceFromFile("resources/sounds/6-EndRound1.mp3");
	soundLib[7] = soundEngine->addSoundSourceFromFile("resources/sounds/7-StillAlive.mp3");
	soundLib[8] = soundEngine->addSoundSourceFromFile("resources/sounds/8-PoohNOTBroken.mp3");
	soundLib[9] = soundEngine->addSoundSourceFromFile("resources/sounds/9-Gas.mp3");
	soundLib[9]->setDefaultVolume(0.2f);
	
}

void init(void) {
	if(god){
		incy = 0.5;
		inca = 0.03;
	}
	
	soundLoad();

	//Hello text
	timer[HELLO] = 30;

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Define the visible faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void resizeWindow(GLsizei w, GLsizei h) {
	wScreen = w;
	hScreen = h;
	//glViewport( 0, 0, wScreen,hScreen );	
	//glutReshapeWindow(wScreen,hScreen);
	glutPostRedisplay();
}

void drawScene() {
	//reloadLightPos();
	int i;

	if (actions[2] == 1)
		ballMoving = drawBall(obsP, lookP, ballMoving, activeTargets);

	//REFLEX�O 
	glEnable(GL_STENCIL_TEST); //Activa o uso do stencil buffer
	glColorMask(0, 0, 0, 0); //Nao escreve no color buffer
	glDisable(GL_DEPTH_TEST); //Torna inactivo o teste de profundidade
	glStencilFunc(GL_ALWAYS, 1, 1); //O
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //

	drawMirrorPlate();

	glColorMask(1, 1, 1, 1); //Activa a escrita de cor
	glEnable(GL_DEPTH_TEST); //Activa o teste de profundidade

	glStencilFunc(GL_EQUAL, 1, 1);//O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Stencil buffer read-only
	
	if (actions[2] == 1) {
		//if (getBallPosition()[2] > 0) {
		glPushMatrix();
		glScalef(1, -1, 1);
		drawBall(obsP, lookP, ballMoving, activeTargets);
		glPopMatrix();
	}

	glDisable(GL_STENCIL_TEST); //Desactiva a utiliza��o do stencil buffer
	
	drawLevel(activeTargets, actions);

	for (i = 0; i < 4; i++) {
		if (checkTargets[i] != activeTargets[i] && !firstTargetHit) {
			firstTargetHit = true;
			soundEngine->play2D(soundLib[3]);
			soundEngine->play2D(soundLib[4]);
		}
		else if (checkTargets[i] != activeTargets[i])
			soundEngine->play2D(soundLib[4]);
	}

	if (checkTargets[4] == false && activeTargets[4] == true && firstRound)
		soundEngine->play2D(soundLib[7]);

	if (checkTargets[4] == true && activeTargets[4] == false) {
		if (!firstRound) {
			soundEngine->play2D(soundLib[5]);
		}
		else {
			firstRound = false;
			timer[PLEASE] = 20;
			soundEngine->play2D(soundLib[5]);
			soundEngine->play2D(soundLib[6]);
		}
	}
}

void display(void) {
	int i;

	if (actions[6] == 1) {
		actions[2] = 0;
		obsP[1]--;
		lookP[0] = rand() % 6;
		lookP[1] = rand() % 6;
		lookP[2] = 0;
	}

	for (i = 0; i < 5; i++) {
		checkTargets[i] = activeTargets[i];
	}
	

	if (!textureDevMode) {
		//Scripting conditionals
		scripting(actions, activeTargets, soundEngine, soundLib, timer);
	}
	else {
		actions[5] = 1;
	}

		printf("actions: SC %d, Gl %d, Ball %d, Star %d, Gtar %d, Fog %d, End %d\n", 
			actions[0], //Scientists speeches		
				actions[1], //Glass animation		
				actions[2], //Ball drawing		
				actions[3], //Small targets drawing		
				actions[4], //Big Target drawing		
				actions[5], //Fog visible		
				actions[6]  //EndLevel Diferenciator		
		);
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, wScreen, hScreen);

	//Allow changing perspective in-game
	glEnable(GL_NORMALIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (defineProj) {
	case 1: gluPerspective(90.0, wScreen / hScreen, 0.1, zC); break;
	default: glOrtho(-xC, xC, -yC, yC, -zC, zC);
		break;
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], lookP[0], lookP[1], lookP[2], 0, 1, 0);
	glDisable(GL_NORMALIZE);

	//Don't mind Nelly Furtado, this keeps the lights on
	lightinit();

	drawScene();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);				// Load Projection Matrix
	glPushMatrix();								// Push Projection
	glLoadIdentity();							// Reset Projection Matrix
	gluOrtho2D(0.0, wScreen, 0.0, hScreen);		// Set Paralel Projection
	glMatrixMode(GL_MODELVIEW);					// Load ModelView Matrix
	glPushMatrix();		// Push ModelView
	glLoadIdentity();							// Reset ModelView Matrix

												//2d code
	load_text(wScreen, hScreen, text, timer);
	if (actions[0] != 0)
	{
		changetimer(actions[0], 30, timer);
		actions[0] = 0;
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glPopMatrix();


	glutSwapBuffers();
}

void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keysNotAscii(int key, int x, int y) {
	if (god) {
		if (key == GLUT_KEY_UP)
			obsP[1] = obsP[1] + incy;
		if (key == GLUT_KEY_DOWN)
			obsP[1] = obsP[1] - incy;
		if (key == GLUT_KEY_LEFT)
			angulo = angulo + inca;
		if (key == GLUT_KEY_RIGHT)
			angulo = angulo - inca;

		if (obsP[1]> yC)
			obsP[1] = yC;
		if (obsP[1]<-yC)
			obsP[1] = -yC;
		obsP[0] = (GLfloat)raio*cos(angulo);
		obsP[2] = (GLfloat)raio*sin(angulo);

		glutPostRedisplay();
		return;
	}

	if (key == GLUT_KEY_UP)
		lookP[1] = lookP[1] + incy;
	if (key == GLUT_KEY_DOWN)
		lookP[1] = lookP[1] - incy;
	if (key == GLUT_KEY_LEFT)
		lookP[0] = lookP[0] - inca;
	if (key == GLUT_KEY_RIGHT)
		lookP[0] = lookP[0] + inca;

	if (lookP[0] < limitsLookP[0])
		lookP[0] = limitsLookP[0];
	if (lookP[0] > limitsLookP[1])
		lookP[0] = limitsLookP[1];
	if (lookP[1] < limitsLookP[0])
		lookP[1] = limitsLookP[0];
	if (lookP[1] > limitsLookP[1])
		lookP[1] = limitsLookP[1];

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	int flag_movement = 0;
	switch (key) {
	case 'r':
	case 'R':
		activeTargets[0] = true;
		activeTargets[1] = true;
		activeTargets[2] = true;
		activeTargets[3] = true;
		activeTargets[4] = false;
		break;
	case 'g':
	case 'G':
		if (god) {
			incy = 1; inca = 1;
			god = !god;
		}
		else {
			incy = 0.5; inca = 0.03;
			god = !god;
		}
		break;
	case ' ':
		if (!ballMoving)
			soundEngine->play2D(soundLib[2]);
		ballMoving = !ballMoving;
		break;
		//--------------------------- Textura no papel de parede
	case 't':
	case 'T':
		glutPostRedisplay();
		break;
		//--------------------------- Projeccao
	case 'q':
	case 'Q':
		defineProj = (defineProj + 1) % 2;
		glutPostRedisplay();
		break;
		//--------------------------- Movimento
	case 'd':
	case 'D':
		if (god) {
			obsP[0] = obsP[0] + incy;
			glutPostRedisplay();
			break;
		}
		obsP[0] = obsP[0] + incy;
		flag_movement = 1;
		if (obsP[0] < limitsWalkP[0]) {
			obsP[0] = limitsWalkP[0];
			flag_movement = 0;
		}
		if (obsP[0] > limitsWalkP[1]) {
			obsP[0] = limitsWalkP[1];
			flag_movement = 0;
		}

		if (flag_movement)
			lookP[0] = lookP[0] + incy;

		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		if (god) {
			obsP[0] = obsP[0] - incy;
			glutPostRedisplay();
			break;
		}
		obsP[0] = obsP[0] - incy;
		flag_movement = 1;
		if (obsP[0] < limitsWalkP[0]) {
			obsP[0] = limitsWalkP[0];
			flag_movement = 0;
		}
		if (obsP[0] > limitsWalkP[1]) {
			obsP[0] = limitsWalkP[1];
			flag_movement = 0;
		}

		if (flag_movement)
			lookP[0] = lookP[0] - incy;

		glutPostRedisplay();
		break;
	case 'w':
	case 'W':
		if (god) {
			keysNotAscii(GLUT_KEY_UP, 0, 0);
			break;
		}
		break;
		obsP[0] = obsP[0] + incy;
		flag_movement = 1;
		if (obsP[0] < limitsWalkP[0]) {
			obsP[0] = limitsWalkP[0];
			flag_movement = 0;
		}
		if (obsP[0] > limitsWalkP[1]) {
			obsP[0] = limitsWalkP[1];
			flag_movement = 0;
		}

		if (flag_movement)
			lookP[0] = lookP[0] + incy;

		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		if (god) {
			keysNotAscii(GLUT_KEY_DOWN, 0, 0);
			break;
		}
		break;
		obsP[0] = obsP[0] + incy;
		flag_movement = 1;
		if (obsP[0] < limitsWalkP[0]) {
			obsP[0] = limitsWalkP[0];
			flag_movement = 0;
		}
		if (obsP[0] > limitsWalkP[1]) {
			obsP[0] = limitsWalkP[1];
			flag_movement = 0;
		}

		if (flag_movement)
			lookP[0] = lookP[0] + incy;

		glutPostRedisplay();
		break;
		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}
}

void createWindow() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(200, 50);
	int window = glutCreateWindow("Moonmen");
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	createWindow();

	init();

	glutSpecialFunc(keysNotAscii);
	glutDisplayFunc(display);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);
	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);

	glutMainLoop();

	soundEngine->drop();
	return 0;
}
