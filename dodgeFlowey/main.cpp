//For windows
//#include <windows.h>
#include <math.h>
#include "Header.h"
#include "level.h"
#include "light.h"

//Dev flags
GLboolean drawAxis = true;

//Coordinate system variables
GLfloat   xC = 70.0, yC = 70.0, zC = 70.0;
GLint     wScreen = 800, hScreen = 600;

//Observer Stuff
GLint    defineView = 0;
GLint    defineProj = 1;
GLfloat  raio = 20;
GLfloat  angulo = 0.35*PI;
GLfloat  obsP[] = { 0, 5, 18.5};
GLfloat  incy = 1;
GLfloat  inca = 1;

GLfloat  lookP[] = { 0, 0};
GLfloat  rayVision = 45;
GLfloat  limitsLookP[] = { -rayVision, rayVision};

GLfloat  posLimit = 6.5;
GLfloat  limitsWalkP[] = { -posLimit, posLimit};

//Time is a woobly thing
GLint    repete = 2;
GLfloat  rr = 1;
GLint    maxR = 20;
GLint    numFrames = 60;              //numero de imagens a colocar em loop na tela
GLint    msec = 100;					//.. definicao do timer (actualizacao)

// Sounds 
irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();


void init(void){
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


void resizeWindow(GLsizei w, GLsizei h){
	wScreen = w;
	hScreen = h;
	//glViewport( 0, 0, wScreen,hScreen );	
	//glutReshapeWindow(wScreen,hScreen);
	glutPostRedisplay();
}


void drawScene() {
	
	drawLevel();
	
	if (drawAxis) {
		//Basic axis
		if(lights_on)
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, wScreen, hScreen);

	//Allow changing perspective in-game
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (defineProj) {
	case 1: gluPerspective(88.0, wScreen / hScreen, 0.1, zC); break;
	default: glOrtho(-xC, xC, -yC, yC, -zC, zC);
		break;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], lookP[0], lookP[1], lookP[2], 0, 1, 0);

	drawScene();
	glutSwapBuffers();
}


void Timer(int value){
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keysNotAscii(int key, int x, int y) {
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
		//keysNotAscii(GLUT_KEY_RIGHT, 0, 0);
		//break;
		obsP[0] = obsP[0] + incy;		
		flag_movement = 1;
		if (obsP[0] < limitsWalkP[0]) {
			obsP[0] = limitsWalkP[0];
			flag_movement = 0;
		}
		if (obsP[0] > limitsWalkP[1]){
			obsP[0] = limitsWalkP[1];
			flag_movement = 0;
		}

		if(flag_movement)
			lookP[0] = lookP[0] + incy;
		
		glutPostRedisplay();		
		break;		
	case 'a':		
	case 'A':
		//keysNotAscii(GLUT_KEY_LEFT,0,0);
		//break;
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
		//keysNotAscii(GLUT_KEY_UP, 0, 0);
		//break;
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
		//keysNotAscii(GLUT_KEY_DOWN, 0, 0);
		//break;
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
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
