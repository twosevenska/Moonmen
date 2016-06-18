#include "Header.h"

void changetimer(int typetimer, int time, int* timer)
{
	timer[typetimer] = time;
}

void load_text(int wScreen, int hScreen, char ** text, int * timer)
{
	int narray;
	for (narray = 0; narray < 7; narray++)
	{
		if (timer[narray]>0)
		{
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_POLYGON);
			glVertex3f(200, 200, -0.1);
			glVertex3f(600, 200, -0.1);
			glVertex3f(600, 400, -0.1);
			glVertex3f(200, 400, -0.1);
			glEnd();
			glTranslatef(wScreen / 2 - 200, hScreen / 2 + 50, 0);
			glScalef(0.3, 0.3, 3);
			glColor3f(1, 1, 1);
			int x = 0;
			int theNcount = 0;
			glBegin(GL_POLYGON);
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
			timer[narray]--;
		}
	}
}