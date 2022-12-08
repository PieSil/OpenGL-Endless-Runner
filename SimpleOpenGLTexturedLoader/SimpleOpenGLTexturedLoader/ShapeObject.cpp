#include "ShapeObject.h"

ShapeObject::ShapeObject(float x, float y, float z, std::shared_ptr<Model> _shape, float speed) : GameObject(x, y, z, speed) {
	shape = std::shared_ptr<Model>(_shape);
}

void ShapeObject::display() {
	//glPushMatrix();
	//glLoadIdentity();
	//glTranslatef(pos_x, pos_y, pos_z);
	shape->display(pos_x, pos_y, pos_z);
	//glPopMatrix();
}

void ShapeObject::update() {
	shape->animate();
}
