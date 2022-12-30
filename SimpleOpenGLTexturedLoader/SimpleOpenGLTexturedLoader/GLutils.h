#pragma once

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)
#define TRUE                1
#define FALSE               0

// assimp include files. These three are usually needed.
#include "assimp.h"
#include "aiPostProcess.h"
#include "aiScene.h"

#include <map>
#include <string.h>

#include "GL/glut.h"
#include <IL/il.h>

//#include "GameLogic.h"

	// currently this is hardcoded
	//static const std::string basepath = "./models/textures/"; //obj..
extern const std::string basepath; //per i file blend
//static const std::string basepath = "./models/"; //per i file blend

// the global Assimp scene object
extern const struct aiScene* scene;
extern GLuint scene_list;
extern struct aiVector3D scene_min, scene_max, scene_center;

// current rotation angle
//extern static float angle = 0.f;

// images / texture
extern std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
extern GLuint* textureIds;							// pointer to texture Array

extern GLfloat LightAmbient[];
extern GLfloat LightDiffuse[];
extern GLfloat LightPosition[];
//double aspectRatio;
//extern const double fieldOfView;

	// ----------------------------------------------------------------------------
void get_bounding_box_for_node(const aiNode* nd, aiVector3D *min, aiVector3D *max, aiMatrix4x4 *trafo);
void get_bounding_box(struct aiVector3D* min, struct aiVector3D* max);
void color4_to_float4(const struct aiColor4D* c, float f[4]);
void set_float4(float f[4], float a, float b, float c, float d);
void apply_material(const struct aiMaterial* mtl);
void Color4f(const struct aiColor4D* color);
void recursive_render(const struct aiScene* sc, const struct aiNode* nd, float scale);
void do_motion(void);
int LoadGLTextures(const aiScene* scene);
int InitGL();
int loadasset(const char* path);
//void mul4x4ByPoint(GLfloat matrix[16], float* x, float* y, float* z, float* w);
//float* mul4x4By4x4(GLfloat matrix[16], float target[16]);
	// ----------------------------------------------------------------------------
	
