#include "GLutils.h"
#include "SphereModel.h"

SphereModel::SphereModel(float _radius, int _slices, int _stack) : radius(_radius), slices(_slices), stack(_stack) {}

void SphereModel::display(float x, float y, float z) {
	//glOrtho(-250, 250, -250, 250, 1 , 1000.0);
	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(x, y, z);
	glutSolidSphere(radius, slices, stack);
	glPopMatrix();
}
