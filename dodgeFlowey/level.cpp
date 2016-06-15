#include "Header.h"
#include "loadBlenderModels.h"

GLuint texture[128];
GLboolean texturesLoaded = false;
RgbImage imag;

void make_plane(GLfloat width, GLfloat height, GLfloat densityValue) {
	//Draw a Plane
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, 1);
	GLint col = 0.0;
	for (GLfloat w = 0.0; w < width; w += densityValue) {
		GLint textureHalf = 0;
		if (col % 2 == 0) {
			for (GLfloat h = 0.0; h <= height; h += densityValue) {
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
}

void drawBlock(GLfloat x, GLfloat y, GLfloat z) {
	//Top
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
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

	glDisable(GL_TEXTURE_2D);
}

void drawWalls(GLfloat x, GLfloat y, GLfloat z) {
	//Ceiling
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(x / 2.0, y, -z);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	make_plane(z * 2, x*2, 4.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Floor
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(x / 2.0, 0, z - 4.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z * 2, x, 4.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Left Wall
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslatef(-x / 2.0, 0, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, y - 4.0, 4.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Right Wall
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslatef(x / 2.0, 0, -z);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, y, 4.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Back Wall
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslatef(-x, 0, -z);
	make_plane(x * 2.0 , y, 4.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Wall Behind
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslatef(x/2.0, 0, z);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	make_plane(x, y, 4.0);
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(HGLASS);
	glPushMatrix();
	glTranslatef(-x / 2.0, y, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, 4.0, 4.0);
	glPopMatrix();
	glDisable(GL_BLEND);
}

void drawCover(GLfloat x, GLfloat y, GLfloat z) {
	//Main Cover
	glPushMatrix();
	glTranslatef( 0.0, 0.0, z - 4.0);
	drawBlock(x, 2.0, 0.2);
	glPopMatrix();

	//First Target Block
	glPushMatrix();
	glTranslatef(-x / 2.0 + x / 4.0, 0.0, z - 8.0);
	drawBlock(x / 2.0, 2.0, 0.8);
	glPopMatrix();

	//Second Target Block
	drawBlock(x / 2.0 , 2.0, 0.8);

	//Third Target Block
	glPushMatrix();
	glTranslatef(x / 2.0 - x / 4.0, 0.0, -z + 4.0);
	drawBlock(x / 2.0, 2.0, 0.8);
	glPopMatrix();
}

void drawCoverGlass(GLfloat x, GLfloat y, GLfloat z) {
	//Glass
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(CGLASS);
	glPushMatrix();
	glTranslatef(-x / 2.0, 0.0, z - 4.1);
	make_plane(x, y, 4.0);
	glPopMatrix();
	glDisable(GL_BLEND);
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
	glTranslatef(x / 2.0 + slide, 0, z - 4.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	make_plane(4.0, x / 2.0, 4.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void drawLevel() {
	if (!texturesLoaded) {
		load_all_level_textures();
		texturesLoaded = true;
	}
	bool lockWindow = false;
	GLfloat glassHeight = 16.0 - 12.0;
	glBlendFunc(GL_ONE, GL_ZERO);
	//drawmodel();
	drawWalls(16.0, 16.0, 20.0);
	drawSpectator(16.0, 12.0, 20.0);
	drawCover(16.0, 16.0, 20.0);
	drawCoverGlass(16.0, glassHeight, 20.0);
	drawTrapFloor(16.0, 16.0, 20.0, 0.0);
	//drawLightPos();
}