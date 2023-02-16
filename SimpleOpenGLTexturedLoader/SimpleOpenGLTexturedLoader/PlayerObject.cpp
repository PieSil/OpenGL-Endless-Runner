#include "PlayerObject.h"
#include "Timer.h"


PlayerObject::PlayerObject(float x, float y, float z, std::shared_ptr<Model> _shape, aiVector3D scale, float speed) : ShapeObject(x, y, z, _shape, scale, speed), onGround(false), jumpSpeed(0), lives(3), inputRecorded(false) {
	shootPowerElapsed = .0;
	shootIntervalElapsed = 0;
	flightPowerElapsed = .0;
	shootIntervalStart = 0;
	shootActive = false;
	flightActive = false;
	shooting = false;
}

void PlayerObject::update() {
	ShapeObject::update();
	if (shootActive) { //countdown to powerup end
		shootPowerElapsed += Timer::getTimer()->getElapsed();
		if (shootPowerElapsed >= SHOOT_POWER_DURATION) {
			setShootActive(false);
			shootPowerElapsed = 0;
			shootIntervalElapsed = 0;
		}
	}

	if (flightActive) { //countdown to powerup end
		flightPowerElapsed += Timer::getTimer()->getElapsed();
		if (flightPowerElapsed >= FLIGHT_DURATION) {
			setFlightActive(false);
			flightPowerElapsed = 0;
		}
	}
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

bool PlayerObject::shoot() {
	bool result = false;
	if (shootActive) {
		shootIntervalElapsed += Timer::getTimer()->getElapsed();
		if (shootIntervalElapsed > PROJECTILE_INTERVAL) {
			result = true;
			shootIntervalStart = glutGet(GLUT_ELAPSED_TIME);
			shootIntervalElapsed = 0;
		}
	}
	return result;
}

float PlayerObject::getRemainingTime(PowerupType pwr)
{
	float result = 0.0f;
	switch (pwr) {
	
	case PowerupType::SHOOT:
		if (shootActive) {
			result = SHOOT_POWER_DURATION - shootPowerElapsed;
		}
		break;
	case PowerupType::FLIGHT:
		if (flightActive) {
			result = FLIGHT_DURATION - flightPowerElapsed;
		}
		break;
	default:
		break;
	}
	return result;
}
