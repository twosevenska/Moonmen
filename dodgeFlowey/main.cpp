//For windows
//#include <windows.h>
#include <math.h>
#include "Header.h"
#include "level.h"

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat   xC = 15.0, yC = 15.0, zC = 100.0;
GLint     wScreen = 800, hScreen = 600;

//------------------------------------------------------------ Observador
GLint    defineView = 0;
GLint    defineProj = 1;
GLfloat  raio = 20;
GLfloat  angulo = 0.35*PI;
GLfloat  obsP[] = { 0.0 , 6.0, 20.0 };
GLfloat  incy = 0.5;
GLfloat  inca = 0.03;

//------------------------------------------------------------ Texturas
GLint    repete = 2;
GLfloat  rr = 1;
GLint    maxR = 20;
GLint    numFrames = 60;              //numero de imagens a colocar em loop na tela
GLint    msec = 100;					//.. definicao do timer (actualizacao)

// Sounds 
irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();


void init(void)
{
	GLfloat localAttCon = 1.0;
	GLfloat localAttLin = 0.05;
	GLfloat localAttQua = 0.0;

	GLfloat GlobalLightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[] = { 0.0f, 10.0f, 0.0f, 1.0f };

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
	
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	//glEnable(GL_NORMALIZE);

	//Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalLightAmbient);
	//Tecto
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, localAttLin);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, localAttQua);
	glEnable(GL_LIGHT0);
}


void resizeWindow(GLsizei w, GLsizei h)
{
	wScreen = w;
	hScreen = h;
	//glViewport( 0, 0, wScreen,hScreen );	
	//glutReshapeWindow(wScreen,hScreen);
	glutPostRedisplay();
}


void drawScene() {
	drawLevel();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixos
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
	glEnable(GL_LIGHTING);
}

void display(void) {

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Apagar ]
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Janela Visualizacao ]
	glViewport(0, 0, wScreen, hScreen);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Projeccao]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (defineProj) {
	case 1: gluPerspective(88.0, wScreen / hScreen, 0.1, zC); break;
	default: glOrtho(-xC, xC, -yC, yC, -zC, zC);
		break;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Modelo+View(camera/observador) ]
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Objectos ]
	drawScene();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}


void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {

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
		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}
}

void teclasNotAscii(int key, int x, int y) {
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
}

//======================================================= MAIN
int main(int argc, char** argv) {
	//Start the background music
	//SoundEngine->play2D("resources/sounds/jacks_office.mp3", GL_FALSE);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(-1, -1);
	glutCreateWindow("Moonmen");

	init();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
