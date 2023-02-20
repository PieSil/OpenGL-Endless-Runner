#include "ShapeObject.h"

ShapeObject::ShapeObject(float x, float y, float z, std::shared_ptr<Model> _shape, aiVector3D scale, float speed) : GameObject(x, y, z, scale, speed) {
	shape = std::shared_ptr<Model>(_shape);
}

ShapeObject::ShapeObject() : GameObject(0, 0, 0, aiVector3D(1,1,1), 0)
{
	shape = nullptr;
}

void ShapeObject::display() {
	//glPushMatrix();
	//glLoadIdentity();
	//glTranslatef(pos_x, pos_y, pos_z);
	shape->display(pos_x, pos_y, pos_z, scale);
	//glPopMatrix();
}

void ShapeObject::update() {}

void ShapeObject::getHitbox(struct aiVector3D* min, struct aiVector3D* max, bool excludeScale) {
	//get bounding box size, then move bbox coordinates to current position

	shape->getHitbox(min, max);

	if (!excludeScale) {
		//apply scale
		min->x /= scale.x;
		min->y /= scale.y;
		min->z /= scale.z;

		max->x /= scale.x;
		max->y /= scale.y;
		max->z /= scale.z;
	}

	min->x += pos_x;
	min->y += pos_y;
	min->z += pos_z;

	max->x += pos_x;
	max->y += pos_y;
	max->z += pos_z;

}

void ShapeObject::setModel(std::shared_ptr<Model> newShape)
{
	shape = newShape;
}
