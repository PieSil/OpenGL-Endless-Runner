#pragma once
#include<list>
#include<vector>

//represents any kind of object that can be rendered, an object should have (at the least) an update function (that may or may not actually do something) and a posisition

class GameObject {
public:
	explicit GameObject(float x, float y, float z, float _speed = 0.);

	virtual void display() = 0;
	virtual void update();

	void move(float x, float y, float z);
	void revertMovement(bool x = true, bool y = true, bool z = true);

	float getPosx() {
		return pos_x;
	}

	float getPosy() {
		return pos_y;
	}

	float getPosz() {
		return pos_z;
	}

protected:
	float pos_x;
	float pos_y;
	float pos_z;
	float prev_x;
	float prev_y;
	float prev_z;
	float speed;
};

