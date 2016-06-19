#include "Header.h"
#include "light.h"
#include "loadBlenderModels.h"
#include "loadTextures.h"



GLboolean texturesLoaded = false;
GLboolean modelsLoaded = false;

GLfloat glassHeight = 16.0;
GLfloat glassHeightDec = 0.0;

GLfloat poisonDensity = 0.0;

GLfloat meshDensity = 2.00;

//Models
const struct aiScene* sans = NULL;
const struct aiScene* papyrus = NULL;

void make_plane(GLfloat width, GLfloat height, GLfloat densityValue) {
	//Draw a Plane
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Color Materials
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_dif);


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
					glTexCoord2f(0.0f, densityValue/2.0);
				}
				glVertex3f(w, h, 0);

				glNormal3f(0.0f, 0.0f, 1.0f);
				if (textureHalf % 2 == 0)
					glTexCoord2f(densityValue / 2.0, 0.0f);
				else
					glTexCoord2f(densityValue / 2.0, densityValue / 2.0);
				glVertex3f(w + densityValue, h, 0);

				textureHalf++;
			}
		}
		else {
			for (GLfloat h = height; h >= 0.0; h -= densityValue) {
				glNormal3f(0.0f, 0.0f, 1.0f);
				if (textureHalf % 2 == 0)
					glTexCoord2f(densityValue / 2.0, 0.0f);
				else
					glTexCoord2f(densityValue / 2.0, densityValue / 2.0);
				glVertex3f(w + densityValue, h, 0);

				glNormal3f(0.0f, 0.0f, 1.0f);
				if (textureHalf % 2 == 0) {
					glTexCoord2f(0.0f, 0.0f);
				}
				else {
					glTexCoord2f(0.0f, densityValue / 2.0);
				}
				glVertex3f(w, h, 0);
				textureHalf++;
			}
		}
		col++;
	}
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
}


void load_all_level_textures() {
	load_texture("floorTile.bmp");
	load_texture("wallTile.bmp");
	load_texture("BlueblockTexture.bmp");
	load_texture("OrangeblockTexture.bmp");
	load_texture("targetOrange.bmp");
	load_texture("targetMask.bmp");
	load_texture("eggman.bmp");
	load_texture("eggmanMask.bmp");
	load_texture("winnieMask.bmp");
	load_texture("winnie.bmp");
	load_texture("blockTexture.bmp");
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
	make_plane(x + 8.0, z * 2, meshDensity);
	glPopMatrix();

	//Floor
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, getTexture("floorTile.bmp"));
	glPushMatrix();
	glTranslatef(x / 2.0, 0, z - 4.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane((z * 2) - 4.0, x, meshDensity);
	glPopMatrix();
	glDisable(GL_BLEND);

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
	glTranslatef(-x / 2.0, 0, -z);
	make_plane(x * 1.0, y, meshDensity);
	glPopMatrix();

	//Wall Behind
	glBindTexture(GL_TEXTURE_2D, getTexture("wallTile.bmp"));
	glPushMatrix();
	glTranslatef(x / 2.0, 0, z);
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

void drawMirrorPlate() {
	//Floor
	glBindTexture(GL_TEXTURE_2D, getTexture("floorTile.bmp"));
	glPushMatrix();
	glTranslatef(8.0, 0, 16.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	make_plane((20 * 2) - 4.0, 16, meshDensity);
	glPopMatrix();
}

void drawCover(GLfloat x, GLfloat y, GLfloat z) {
	//Main Cover
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("blockTexture.bmp"));
	glPushMatrix();
	glTranslatef(0.0, 0.0, z - 6.0);
	drawBlock(x, 2.0, 0.2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//First Target Block -6,0,10
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("BlueblockTexture.bmp"));
	glPushMatrix();
	glTranslatef(-x / 2.0 + x / 4.0, 0.0, z - 10.0);
	drawBlock(x / 2.0, 2.0, 1.6);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Second Target Block 0,0,0
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("OrangeblockTexture.bmp"));
	drawBlock(x / 2.0, 2.0, 1.6);
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
	glTranslatef(-x / 2.0, y, z - 6.1);
	make_plane(x, 16.0, 4.0);
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

		if (sans != NULL)
			modelsLoaded = true;
		else {
			std::cout << "Failed loading models @drawModels";
		}
	}
	glPushMatrix();
	glTranslatef(-10.0, 11.0, -6.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glScalef(0.7, 0.7, 0.7);
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
	/*if (lights_on)
		glDisable(GL_LIGHTING);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glColor4f(CGLASS);
	
	glTranslatef(x, y, z);
	glRotatef(rot, 0.0, 0.0, 1.0);
	glTranslatef(-1.0, -1.0, 0.0);
	make_plane(2.0, 2.0, 0.4);
	glPopMatrix();
	glDisable(GL_BLEND);

	if (lights_on)
		glEnable(GL_LIGHTING);*/

	GLfloat pos[3] = {x,y,z};
	GLfloat dim[3] = {2.0,2.0,2.0};

	glPushMatrix();
	glTranslatef(0.0, -0.5, 0.0);
	createMaskedTextureObject("targetMask.bmp", "targetOrange.bmp", pos, dim, rot,false);
	glPopMatrix();
}

void drawBigTarget(GLfloat rot, GLboolean bad) {
	GLfloat pos[3] = { 0,0,0 };
	GLfloat dim[3] = { 6.0, 6.0, 6.0 };

	glPushMatrix();
	glTranslatef(-2.0, 3.0, 0.0);
	if(bad)
		createMaskedTextureObject("eggmanMask.bmp", "eggman.bmp", pos, dim, rot,true);
	else
		createMaskedTextureObject("winnieMask.bmp", "winnie.bmp", pos, dim, rot,true);
	glPopMatrix();

}

void drawTargets(GLfloat x, GLfloat z, GLfloat alt, GLboolean *activeTargets) {
	//First block targets
	if (activeTargets[0])
		drawSmallTarget(-x / 2.0 + 2.0, alt, z - 10.2, 0.0);
	if (activeTargets[1])
		drawSmallTarget(-x / 2.0 + 6.0, alt, z - 10.2, 0.0);

	//Last block targets
	if (activeTargets[2])
		drawSmallTarget(x / 2.0 - 6.0, alt, -z + 4.2, 0.0);
	if (activeTargets[3])
		drawSmallTarget(x / 2.0 - 2.0, alt, -z + 4.2, 0.0);

	if (activeTargets[4])
		drawBigTarget(0.0, true);
}

void drawLevel(GLboolean *activeTargets, GLint *actions) {
	GLfloat x = 16.0;
	GLfloat y = 16.0;
	GLfloat z = 20.0;

	if (!texturesLoaded) {
		load_all_level_textures();
		texturesLoaded = true;
	}
	bool lockWindow = false;
	GLfloat glassHeight = y - 12.0;
	//drawModels(x, y, z);
	drawWalls(x, y, z);
	drawSpectator(x, y - 4.0, z);

	drawCover(x, y, z);


	if(actions[3] == 2)
		drawTargets(x, z, 3.5, activeTargets);

	if (glassHeightDec <= -16.0)
		actions[1] = 0;
	if (glassHeightDec > -16.0 && actions[1] == 1)
		glassHeightDec -= 0.2;

	drawCoverGlass(x, glassHeightDec, z);

	if (actions[4] == 1 && activeTargets[4])
		drawBigTarget(0.0, true);

	if (actions[5] == 1) {
		drawFog(5.0, poisonDensity);
		poisonDensity += 0.005;
	}
	if (poisonDensity > 0.25) {
		actions[5] = 2;
	}
	drawTrapFloor(x, y, z, 0.0);
}