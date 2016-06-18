//For windows
//#include <windows.h>
#include <math.h>
#include "Header.h"
#include "level.h"
#include "light.h"
#include "ballz.h"
#include "script.h"
#include "text.h"

char *text[] = { "","HELLO.", "FOLLOW", "WAIT!","HIT!","PLEASE", "TRUST ME!", "DON'T" };
int timer[] = { 0,0,0,0,0,0,0,0 };


//Dev flags
GLboolean god = false;
GLboolean drawAxis = false;

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
GLboolean activeTargets[5] = { true, true, true, true, true};

//Scripting
//Scientists, Glass, Ball, Small Targets, Big Target, Fog, EndLevel 
GLint actions[7] = { 0, 0, 0, 0, 0, 0, 0 };

//Time is a woobly thing
GLint    repete = 2;
GLfloat  rr = 1;
GLint    maxR = 20;
GLint    numFrames = 60;              //numero de imagens a colocar em loop na tela
GLint    msec = 100;					//.. definicao do timer (actualizacao)

										// Sounds 
irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();

void init(void) {
	actions[0] = HELLO;
	if(god){
		incy = 0.5;
		inca = 0.03;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Define the visible faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Don't mind Nelly Furtado, this keeps the lights on
	lightinit();
}


void resizeWindow(GLsizei w, GLsizei h) {
	wScreen = w;
	hScreen = h;
	//glViewport( 0, 0, wScreen,hScreen );	
	//glutReshapeWindow(wScreen,hScreen);
	glutPostRedisplay();
}

void drawScene() {
	int i;
	reloadLightPos();
	GLboolean backupTargets[5];
	for (i = 0; i < 5; i++)
	{
		backupTargets[i] = activeTargets[i];
	}
	if(actions[2])
		ballMoving = drawBall(obsP, lookP, ballMoving, activeTargets);
	drawLevel(activeTargets, actions);

	for (i = 0; i < 5; i++)
	{
		if (backupTargets[i] != activeTargets[i])
		{
			changetimer(HIT, 10, timer);
		}
	}

	if (drawAxis) {
		//Basic axis
		if (lights_on)
			glDisable(GL_LIGHTING);

		glColor4f(PURPLE);
		glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(10, 0, 0);
		glEnd();
		glColor4f(ORANGE);
		glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 10, 0);
		glEnd();
		glColor4f(BLUE);
		glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 10);
		glEnd();

		if (lights_on)
			glEnable(GL_LIGHTING);
	}
}

void display(void) {

	scripting(actions);

	printf("actions: SC %d, Gl %d, Ball %d, Star %d, Gtar %d, Fog %d, End %d\n",
		actions[0], //Scientists speeches
		actions[1], //Glass animation
		actions[2], //Ball drawing
		actions[3], //Small targets drawing
		actions[4], //Big Target drawing
		actions[5], //Fog visible
		actions[6]  //EndLevel Diferenciator
		);

	if (actions[6] == 2) {
		MessageBox(0, "Pity", NULL, MB_OK | MB_ICONSTOP);
		exit(0);
	}

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
	drawScene();
	//2d
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
	//
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
		activeTargets[4] = true;
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
	//Start the background music
	//SoundEngine->play2D("resources/sounds/jacks_office.mp3", GL_FALSE);
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

	return 0;
}
