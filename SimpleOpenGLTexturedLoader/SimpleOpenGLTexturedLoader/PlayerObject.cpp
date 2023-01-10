#include "PlayerObject.h"
#include "Timer.h"

PlayerObject::PlayerObject(float x, float y, float z, std::shared_ptr<Model> _shape, float speed) : ShapeObject(x, y, z, _shape, speed), onGround(false), jumpSpeed(0), lives(3) {}

void PlayerObject::update() {
	ShapeObject::update();
	fall();
}

void PlayerObject::fall() {
	//applies "gravity" to object not on the ground

	if (!onGround) {
 		double elapsedTime = Timer::getTimer()->getElapsed();
		prev_y = pos_y;
		pos_y += jumpSpeed * elapsedTime;
		jumpSpeed -= 50 * elapsedTime;
	}
}
