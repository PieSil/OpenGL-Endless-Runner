#pragma once
#include<list>
#include<vector>
#include "GLutils.h"

//represents any kind of object that can be rendered, an object should have (at the least) an update function (that may or may not actually do something) and a posisition

class GameObject {
public:
	explicit GameObject(float x, float y, float z, aiVector3D scale = aiVector3D(1,1,1), float _speed = 0.);

	virtual void display() = 0;
	virtual void update();

	virtual void move(float spd = 0);
	virtual void revertMovement(bool x = true, bool y = true, bool z = true);

	float getPosx() {
		return pos_x;
	}

	float getPosy() {
		return pos_y;
	}

	float getPosz() {
		return pos_z;
	}

	void setPosX(float value) {
		pos_x = value;
	}

	void setPosY(float value) {
		pos_y = value;
	}

	void setPosZ(float value) {
		pos_z = value;
	}

	float getXSpeed() {
		return xSpeed;
	}

	float getYSpeed() {
		return ySpeed;
	}

	float getZSpeed() {
		return zSpeed;
	}

	void incrXSpeed(int incr) {
		xSpeed += incr;
		if (xSpeed > 1.) {
			xSpeed = 1.;
		} else if (xSpeed < -1.) {
			xSpeed = -1.;
		}
	}

	void incrYSpeed(int incr) {
		ySpeed += incr;
		if (ySpeed > 1.) {
			ySpeed = 1.;
		}
		else if (ySpeed < -1.) {
			ySpeed = -1.;
		}
	}

	void incrZSpeed(int incr) {
		zSpeed += incr;
		if (zSpeed > 1.) {
			zSpeed = 1.;
		}
		else if (zSpeed < -1.) {
			zSpeed = -1.;
		}
	}

	void resetXSpeed() {
		xSpeed = 0.;
	}

	void resetYSpeed() {
		ySpeed = 0.;
	}

	void resetZSpeed() {
		zSpeed = 0.;
	}

	float getSpeed() {
		return speed;
	}

	void setScale(aiVector3D scale) {
		this->scale = scale;
	}

protected:
	float pos_x;
	float pos_y;
	float pos_z;
	float prev_x;
	float prev_y;
	float prev_z;
	float speed;
	float xSpeed;
	float ySpeed;
	float zSpeed;
	aiVector3D scale;
};

