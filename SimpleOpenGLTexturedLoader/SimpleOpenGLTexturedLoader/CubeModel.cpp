#include "CubeModel.h"

CubeModel::CubeModel(float _size) : size(_size) {}

void CubeModel::display(float x, float y, float z, aiVector3D scale, bool ortho) {
	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(x, y, z);
	glutSolidCube(size);
	glPopMatrix();
}

void CubeModel::getHitbox(struct aiVector3D* min, struct aiVector3D* max)
{
}
