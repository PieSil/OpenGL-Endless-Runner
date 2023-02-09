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

void ShapeObject::update() {}

void ShapeObject::getHitbox(struct aiVector3D* min, struct aiVector3D* max) {
	//get bounding box size, then move bbox coordinates to current position

	shape->getHitbox(min, max); 
	min->x += pos_x;
	min->y += pos_y;
	min->z += pos_z;

	max->x += pos_x;
	max->y += pos_y;
	max->z += pos_z;
}
