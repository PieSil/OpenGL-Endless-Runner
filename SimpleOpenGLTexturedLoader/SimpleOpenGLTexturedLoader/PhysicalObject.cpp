#include "PhysicalObject.h"
#include "Timer.h"

PhysicalObject::PhysicalObject(float x, float y, float z, std::shared_ptr<Model> _shape, float speed) : ShapeObject(x, y, z, _shape, speed), onGround(false), vertSpeed(0) {}

void PhysicalObject::update() {
	ShapeObject::update();
	fall();
}

void PhysicalObject::fall() {
	//applies "gravity" to object not on the ground

	if (!onGround) {
		double elapsedTime = Timer::getTimer()->getElapsed();
		prev_y = pos_y;
		pos_y += vertSpeed * elapsedTime;
		vertSpeed -= 0.00005;
	}
}
