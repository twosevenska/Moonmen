#include "Header.h"


void changetimer(int typetimer, int time, int* timer)
{
	timer[typetimer] = time;
}

void crosshair(int wScreen, int hScreen)
{
	glEnable(GL_COLOR_MATERIAL);
	
	glColor3f(1, 0, 0);

	//GLfloat mat_cross[] = {1.0,0.0,0.0,1.0};
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_cross);

	glBegin(GL_POLYGON);
	glVertex3f(wScreen / 2 - 4, hScreen / 2 - 4, -0.5);
	glVertex3f(wScreen / 2 + 4, hScreen / 2 - 4, -0.5);
	glVertex3f(wScreen / 2 + 4, hScreen / 2 + 4, -0.5);
	glVertex3f(wScreen / 2 - 4, hScreen / 2 + 4, -0.5);
	glEnd();
	glColor3f(0.6,0.6,0.6);
	glDisable(GL_COLOR_MATERIAL);
}

void load_text(int wScreen, int hScreen, char ** text, int * timer)
{
	int narray;
	for (narray = 0; narray < 5; narray++)
	{
		if (timer[narray]>0)
		{
			if (timer[HELLO]) {
				glEnable(GL_COLOR_MATERIAL);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_BLEND);
				glColor4f( 0, 0, 0.1, 0.2);
				glPushMatrix();
				glBegin(GL_POLYGON);
					glVertex3f(0, 0, -0.1);
					glVertex3f(wScreen, 0, -0.1);
					glVertex3f(wScreen, hScreen, -0.1);
					glVertex3f(0, hScreen, -0.1);
				glEnd();
				glPopMatrix();
				glDisable(GL_BLEND);
				glDisable(GL_COLOR_MATERIAL);
			}
			glTranslatef(wScreen / 2 - 100, hScreen - 150, 0);
			glScalef(0.5, 0.5, 0.001);
			glColor3f(0,0, 0);
			int x = 0;
			int theNcount = 0;
			glEnable(GL_COLOR_MATERIAL);
			for (int i = 0; i < strlen(text[narray]); i++)
			{
				x += glutStrokeWidth(GLUT_STROKE_ROMAN, text[narray][i]);
				glutStrokeCharacter(GLUT_STROKE_ROMAN, text[narray][i]);
				if ((i + theNcount) % 19 == 0 && i != 0)
				{
					glTranslatef(-x, -200, 0);
					x = 0;
				}

				if (text[narray][i] == '\n')
				{
					while ((i + theNcount) % 17 != 0)
					{
						glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');
						theNcount++;
						x += glutStrokeWidth(GLUT_STROKE_ROMAN, ' ');
					}
					glTranslatef(-x, -200, 0);
					x = 0;
				}
			}
			glDisable(GL_COLOR_MATERIAL);
			glEnd();
			timer[narray]--;
		}
	}
	glColor3f(0.6, 0.6, 0.6);
	/*
	if (flag == 0){
		crosshair(wScreen, hScreen);
	}*/
}
