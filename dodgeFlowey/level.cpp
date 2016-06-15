#include "Header.h"
#include "loadBlenderModels.h"

GLuint texture[128];
GLboolean texturesLoaded = false;
RgbImage imag;

void make_plane(GLfloat width, GLfloat height, GLfloat densityValue) {
	//Draw a Plane
	glBegin(GL_TRIANGLE_STRIP);
	GLint col = 0.0;
	for (GLfloat w = 0.0; w < width; w += densityValue) {
		GLint textureHalf = 0;
		if (col % 2 == 0) {
			for (GLfloat h = 0.0; h <= height; h += densityValue) {
				
				glNormal3f(0.0f, 0.0f, 1.0f);
				if (textureHalf % 2 == 0) {
					glTexCoord2f(0.0f, 0.0f);
				}
				else {
					glTexCoord2f(0.0f, 1.0f);
				}
				glVertex3f(w, h, 0);

				glNormal3f(0.0f, 0.0f, 1.0f);
				if (textureHalf % 2 == 0)
					glTexCoord2f(1.0f, 0.0f);
				else
					glTexCoord2f(1.0f, 1.0f);
				glVertex3f(w + densityValue, h, 0);
				textureHalf++;
			}
		}else{
			for (GLfloat h = height; h >= 0.0; h -= densityValue) {
				if (textureHalf % 2 == 0) {
					glTexCoord2f(0.0f, 0.0f);
				}
				else {
					glTexCoord2f(0.0f, 1.0f);
				}
				glVertex3f(w, h, 0);
				if (textureHalf % 2 == 0)
					glTexCoord2f(1.0f, 0.0f);
				else
					glTexCoord2f(1.0f, 1.0f);
				glVertex3f(w + densityValue, h, 0);
				textureHalf++;
			}
		}
		col++;
	}
	glEnd();
}

void load_texture(std::string name, GLint texId) {
	glGenTextures(1, &texture[texId]);
	glBindTexture(GL_TEXTURE_2D, texture[texId]);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	std::string textureLocation = "resources/textures/" + name;
	const char * tl = textureLocation.c_str();
	imag.LoadBmpFile(tl);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imag.GetNumCols(), imag.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}

void load_all_level_textures() {
	load_texture("floorTile.bmp", 0);
	load_texture("wallTile.bmp", 1);
	load_texture("blockTexture.bmp", 2);
	load_texture("BlueblockTexture.bmp", 3);
	load_texture("OrangeblockTexture.bmp", 4);
}

void drawBlock(GLfloat x, GLfloat y, GLfloat z) {
	//Top
	glPushMatrix();
	glTranslatef(-x / 2.0, y, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	make_plane(x, z, 0.05);
	glPopMatrix();

	//Back
	glPushMatrix();
	glTranslatef(x / 2.0, 0.0, -z);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	make_plane(x, y, 0.05);
	glPopMatrix();

	//Front
	glPushMatrix();
	glTranslatef(-x / 2.0, 0.0, 0.0);
	make_plane(x, y, 0.05);
	glPopMatrix();

	//LeftSide
	glPushMatrix();
	glTranslatef(-x / 2.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z, y, 0.05);
	glPopMatrix();

	//RightSide
	glPushMatrix();
	glTranslatef(x / 2.0, 0.0, -z);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	make_plane(z, y, 0.05);
	glPopMatrix();
}

void drawWalls(GLfloat x, GLfloat y, GLfloat z) {
	GLfloat meshDensity = 4.0;

	//Ceiling
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(x / 2.0, y, -z);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	make_plane(z * 2, x*2, meshDensity);
	glPopMatrix();

	//Floor
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(x / 2.0, 0, z - 4.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z * 2, x, meshDensity);
	glPopMatrix();

	//Left Wall
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslatef(-x / 2.0, 0, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, y - 4.0, meshDensity);
	glPopMatrix();

	//Right Wall
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslatef(x / 2.0, 0, -z);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, y, meshDensity);
	glPopMatrix();

	//Back Wall
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslatef(-x, 0, -z);
	make_plane(x * 2.0 , y, meshDensity);
	glPopMatrix();

	//Wall Behind
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslatef(x/2.0, 0, z);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	make_plane(x, y, meshDensity);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void drawSpectator(GLfloat x, GLfloat y, GLfloat z) {

	//Left Wall
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslatef(-x, y, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, 4.0, 4.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Glass
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(HGLASS);
	glPushMatrix();
	glTranslatef(-x / 2.0, y, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, 4.0, 4.0);
	glPopMatrix();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}

void drawCover(GLfloat x, GLfloat y, GLfloat z) {
	//Main Cover
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
	glTranslatef( 0.0, 0.0, z - 4.0);
	drawBlock(x, 2.0, 0.2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//First Target Block
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPushMatrix();
	glTranslatef(-x / 2.0 + x / 4.0, 0.0, z - 8.0);
	drawBlock(x / 2.0, 2.0, 1.6);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Second Target Block
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	drawBlock(x / 2.0 , 2.0, 1.6);
	glDisable(GL_TEXTURE_2D);

	//Third Target Block
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPushMatrix();
	glTranslatef(x / 2.0 - x / 4.0, 0.0, -z + 4.0);
	drawBlock(x / 2.0, 2.0, 1.6);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawCoverGlass(GLfloat x, GLfloat y, GLfloat z) {
	//Glass
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glColor4f(CGLASS);
	glPushMatrix();
	glTranslatef(-x / 2.0, 0.0, z - 4.1);
	make_plane(x, y, 4.0);
	glPopMatrix();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}

void drawTrapFloor(GLfloat x, GLfloat y, GLfloat z, GLfloat slide) {
	//Left Segment
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(-x / 2.0 - slide, 0, z - 4.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	make_plane(4.0, x / 2.0, 4.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Right Segment
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(x / 2.0 + slide, 0.0, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	make_plane(4.0, x / 2.0, 4.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawModels(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(-12.0, 11.0, -6.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	drawmodel();
	glPopMatrix();
}

void drawFog(GLfloat distance, GLfloat density) {
	GLfloat	fogColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density);
	/*
		gl_dont_care - Lets opengl choose the kind of fog (per vertex of per pixel) and an unknown formula.
		gl_nicest - Makes the fog per pixel (look good)
		glfastest - Makes the fog per vertex (faster, but less nice)
	*/
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, distance);
	glFogf(GL_FOG_END, 16.0f);							
	glEnable(GL_FOG);									
}

void drawLightPos() {
	glPushMatrix();
	glColor4f(YELLOW);
	glTranslatef(0.0, 10.0, 0.0);
	glutSolidSphere(0.2, 250, 250);
	glPopMatrix();
}

void drawLevel() {
	if (!texturesLoaded) {
		load_all_level_textures();
		texturesLoaded = true;
	}
	bool lockWindow = false;
	GLfloat glassHeight = 16.0 - 12.0;
	//drawModels(16.0, 16.0, 20.0);
	drawWalls(16.0, 16.0, 20.0);
	drawLightPos();
	drawSpectator(16.0, 12.0, 20.0);
	//drawFog(5.0, 0.01);
	drawCover(16.0, 16.0, 20.0);
	drawCoverGlass(16.0, glassHeight, 20.0);
	drawTrapFloor(16.0, 16.0, 20.0, 0.0);
}