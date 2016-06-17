#include "Header.h"
#include <map>
// assimp include files. These three are usually needed.
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/postprocess.h"
#include "assimp/scene.h"


std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds

// Create an instance of the Importer class
Assimp::Importer importer[10];
GLint importerId = 0;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)


const struct aiScene* loadasset(const char* path){
	const struct aiScene* scene;
	// we are taking one of the postprocessing presets to avoid
	// spelling out 20+ single postprocessing flags here.
	scene = importer[importerId].ReadFile(path, aiProcessPreset_TargetRealtime_Quality);
	importerId++;
	return scene;
}

void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void color4_to_float4(const aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void apply_material(const aiMaterial *mtl)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	float shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;	// changed: to unsigned

	int texIndex = 0;
	aiString texPath;	//contains filename of texture

	unsigned int numTextures = mtl->GetTextureCount(aiTextureType_DIFFUSE);
	/*if (numTextures > 0 && AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
	{
		//bind texture
 		unsigned int texId = *textureIdMap[texPath.data];
		glBindTexture(GL_TEXTURE_2D, texId);
	}
	*/
	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	max = 1;
	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
	if ((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if (AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if ((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void renderModel(const struct aiScene *sc, const struct aiNode* nd) {
	unsigned int i;
	unsigned int n = 0, t;
	aiMatrix4x4 m = nd->mTransformation;

	// update transform
	m.Transpose();
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];

		//apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		if (mesh->mNormals == NULL) {
			glDisable(GL_LIGHTING);
		}
		else {
			glEnable(GL_LIGHTING);
		}

		/*if (mesh->mColors[0] != NULL)
		{
			glEnable(GL_COLOR_MATERIAL);
		}
		else
		{
			glDisable(GL_COLOR_MATERIAL);
		}*/

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch (face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for (i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];

				if (mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if (mesh->mNormals != NULL)
					/*if (mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
					{
						glTexCoord2f(mesh->mTextureCoords[0][index].x, 1 - mesh->mTextureCoords[0][index].y); //mTextureCoords[channel][vertex]
					}*/
					glNormal3fv(&mesh->mNormals[index].x);
					glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		renderModel(sc, nd->mChildren[n]);
	}

	glPopMatrix();
}

const struct aiScene* loadModel(std::string name) {
	std::string objLocation = "resources/models/" + name;
	const char * ol = objLocation.c_str();
	const struct aiScene* scene = loadasset(ol);
	if (!scene) {
		printf("\nCAN'T LOAD OBJ\n");
		exit(0);
	}
	return scene;
}

void drawmodel(const struct aiScene* scene){
	if(scene != NULL){
		//std::cout << "There were two,  the one in the middle fell.\n";
		renderModel(scene, scene->mRootNode);
	}else{
		//std::cout << "Warning, received a null scene to draw! Ignoring.\n";
	}
}