#include "Header.h"
#include "light.h"
#include "loadBlenderModels.h"
#include "loadTextures.h"



GLboolean texturesLoaded = false;
GLboolean modelsLoaded = false;


GLfloat meshDensity = 2.00;

//Models
const struct aiScene* sans = NULL;
const struct aiScene* papyrus = NULL;

void make_plane(GLfloat width, GLfloat height, GLfloat densityValue) {
	//Draw a Plane
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
				glNormal3f(0.0f, 0.0f, 1.0f);
				if (textureHalf % 2 == 0)
					glTexCoord2f(1.0f, 0.0f);
				else
					glTexCoord2f(1.0f, 1.0f);
				glVertex3f(w + densityValue, h, 0);

				glNormal3f(0.0f, 0.0f, 1.0f);
				if (textureHalf % 2 == 0) {
					glTexCoord2f(0.0f, 0.0f);
				}
				else {
					glTexCoord2f(0.0f, 1.0f);
				}
				glVertex3f(w, h, 0);
				textureHalf++;
			}
		}
		col++;
	}
	glEnd();
}


void load_all_level_textures() {
	load_texture("floorTile.bmp");
	load_texture("wallTile.bmp");
	load_texture("blockTexture.bmp");
	load_texture("BlueblockTexture.bmp");
	load_texture("OrangeblockTexture.bmp");
	load_texture("targetOrange.bmp");
	load_texture("targetMask.bmp");
}

void drawBlock(GLfloat x, GLfloat y, GLfloat z) {
	GLfloat density = 0.4;
	//Top
	glPushMatrix();
	glTranslatef(-x / 2.0, y, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	make_plane(x, z, 0.02);
	glPopMatrix();

	//Back
	glPushMatrix();
	glTranslatef(x / 2.0, 0.0, -z);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	make_plane(x, y, density);
	glPopMatrix();

	//Front
	glPushMatrix();
	glTranslatef(-x / 2.0, 0.0, 0.0);
	make_plane(x, y, density);
	glPopMatrix();

	//LeftSide
	glPushMatrix();
	glTranslatef(-x / 2.0, 0.0, -z);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	make_plane(z, y, density);
	glPopMatrix();

	//RightSide
	glPushMatrix();
	glTranslatef(x / 2.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z, y, density);
	glPopMatrix();
}

void drawWalls(GLfloat x, GLfloat y, GLfloat z) {

	//Ceiling
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("floorTile.bmp"));
	glPushMatrix();
	glTranslatef(-x, y, -z);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	make_plane(x+8.0, z * 2, meshDensity);
	glPopMatrix();

	//Floor
	glBindTexture(GL_TEXTURE_2D, getTexture("floorTile.bmp"));
	glPushMatrix();
	glTranslatef(x / 2.0, 0, z - 4.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane((z * 2) - 4.0, x, meshDensity);
	glPopMatrix();

	//Left Wall
	glBindTexture(GL_TEXTURE_2D, getTexture("wallTile.bmp"));
	glPushMatrix();
	glTranslatef(-x / 2.0, 0, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, y - 4.0, meshDensity);
	glPopMatrix();

	//Right Wall
	glBindTexture(GL_TEXTURE_2D, getTexture("wallTile.bmp"));
	glPushMatrix();
	glTranslatef((x / 2.0) + 0.0, 0, -z);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, y, meshDensity);
	glPopMatrix();

	//Back Wall
	glBindTexture(GL_TEXTURE_2D, getTexture("wallTile.bmp"));
	glPushMatrix();
	glTranslatef(-x/2.0, 0, -z);
	make_plane(x * 1.0 , y, meshDensity);
	glPopMatrix();

	//Wall Behind
	glBindTexture(GL_TEXTURE_2D, getTexture("wallTile.bmp"));
	glPushMatrix();
	glTranslatef(x/2.0, 0, z);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	make_plane(x, y, meshDensity);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void drawSpectator(GLfloat x, GLfloat y, GLfloat z) {

	//Back Wall
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("wallTile.bmp"));
	glPushMatrix();
	glTranslatef(-x, y - x / 4.0, -z);
	make_plane(x / 2.0, x / 2.0, meshDensity);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Left Wall
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("wallTile.bmp"));
	glPushMatrix();
	glTranslatef(-x, y, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, 4.0, meshDensity);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Glass
	if (lights_on)
		glDisable(GL_LIGHTING);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(HGLASS);
	glPushMatrix();
	glTranslatef(-x / 2.0, y, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane(z*2.0, 4.0, meshDensity);
	glPopMatrix();
	glDisable(GL_BLEND);
	
	if (lights_on)
		glEnable(GL_LIGHTING);
}

void drawCover(GLfloat x, GLfloat y, GLfloat z) {
	//Main Cover
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("blockTexture.bmp"));
	glPushMatrix();
	glTranslatef( 0.0, 0.0, z - 6.0);
	drawBlock(x, 2.0, 0.2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//First Target Block
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("BlueblockTexture.bmp"));
	glPushMatrix();
	glTranslatef(-x / 2.0 + x / 4.0, 0.0, z - 10.0);
	drawBlock(x / 2.0, 2.0, 1.6);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Second Target Block
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("OrangeblockTexture.bmp"));
	drawBlock(x / 2.0 , 2.0, 1.6);
	glDisable(GL_TEXTURE_2D);

	//Third Target Block
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("BlueblockTexture.bmp"));
	glPushMatrix();
	glTranslatef(x / 2.0 - x / 4.0, 0.0, -z + 4.0);
	drawBlock(x / 2.0, 2.0, 1.6);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawCoverGlass(GLfloat x, GLfloat y, GLfloat z) {
	//Glass
	if (lights_on)
		glDisable(GL_LIGHTING);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glColor4f(CGLASS);
	glPushMatrix();
	glTranslatef(-x / 2.0, 0.0, z - 6.1);
	make_plane(x, y, 4.0);
	glPopMatrix();
	glDisable(GL_BLEND);
	
	if (lights_on)
		glEnable(GL_LIGHTING);
}

void drawTrapFloor(GLfloat x, GLfloat y, GLfloat z, GLfloat slide) {
	//Left Segment
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("floorTile.bmp"));
	glPushMatrix();
	glTranslatef(-x / 2.0 - slide, 0, z - 4.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	make_plane(4.0, x / 2.0, meshDensity);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Right Segment
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("floorTile.bmp"));
	glPushMatrix();
	glTranslatef(x / 2.0 + slide, 0.0, z);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	make_plane(4.0, x / 2.0, meshDensity);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawModels(GLfloat x, GLfloat y, GLfloat z) {
	if (!modelsLoaded) {
		sans = loadModel("Sans/Pre-Posed/Sans_Figure_Pose.obj");
		papyrus = loadModel("Papyrus/Pre-posed/Papyrus_Figure_Pose.obj");
		
		if(sans != NULL)
			modelsLoaded = true;
		else {
			std::cout << "Failed loading models @drawModels";
		}
	}
	glPushMatrix();
	glTranslatef(-10.0, 11.0, -6.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glScalef(0.7,0.7,0.7);
	drawmodel(sans);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-11.0, 11.0, -10.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glScalef(0.5, 0.7, 0.7);
	drawmodel(papyrus);
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

void drawSmallTarget(GLfloat x, GLfloat y, GLfloat z, GLfloat rot) {
	if (lights_on)
		glDisable(GL_LIGHTING);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glColor4f(CGLASS);
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rot, 0.0, 0.0, 1.0);
	glTranslatef(-1.0,-1.0,0.0);
	make_plane(2.0, 2.0, 0.4);
	glPopMatrix();
	glDisable(GL_BLEND);

	if (lights_on)
		glEnable(GL_LIGHTING);

	createMaskedTextureObject("targetMask.bmp", "targetOrange.bmp",  x,  y,  z,  rot);
}

void drawTargets(GLfloat x, GLfloat z, GLfloat alt) {

	//First block targets
	drawSmallTarget(-x / 2.0 + 2.0 , alt, z - 10.2, 0.0);
	drawSmallTarget(-x / 2.0 + 6.0, alt, z - 10.2, 0.0);

	//Last block targets
	drawSmallTarget(x / 2.0 - 2.0, alt, -z + 4.2, 0.0);
	drawSmallTarget(x / 2.0 - 6.0, alt, -z + 4.2, 0.0);
}

void drawLevel() {
	GLfloat x = 16.0;
	GLfloat y = 16.0;
	GLfloat z = 20.0;

	if (!texturesLoaded) {
		load_all_level_textures();
		texturesLoaded = true;
	}
	bool lockWindow = false;
	GLfloat glassHeight = y - 12.0;
	drawModels(x, y, z);
	drawWalls(x, y, z);
	drawSpectator(x, y - 4.0, z);
	//drawFog(5.0, 0.01);
	drawCover(x, y, z);
	drawTargets(x, z, 3.0);
	drawCoverGlass(x, glassHeight, z);
	drawTrapFloor(x, y, z, 0.0);
}