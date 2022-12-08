#include "CubeModel.h"

CubeModel::CubeModel(float _size) : size(_size) {}

void CubeModel::display(float x, float y, float z) {
	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(x, y, z);
	glutSolidCube(size);
	glPopMatrix();
}
