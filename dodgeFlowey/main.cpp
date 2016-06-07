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
GLfloat  obsP[] = { raio*cos(angulo), 5.5, raio*sin(angulo) };
GLfloat  incy = 0.5;
GLfloat  inca = 0.03;
GLfloat  angBule = 0;
GLfloat  incBule = 10;

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
	glClearColor(SWHITE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
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
	//TODO: mudar imagem na tela
	angBule = angBule + incBule;
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
