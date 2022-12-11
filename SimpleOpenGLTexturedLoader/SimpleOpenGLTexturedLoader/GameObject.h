#pragma once
#include<list>
#include<vector>

//represents any kind of object that can be rendered, an object should have (at the least) an update fucntion (that may or may not actualyy do something) and a posisition

class GameObject {
public:
	explicit GameObject(float x, float y, float z, float _speed = 0.);

	virtual void display() = 0;
	virtual void update();

	void move(float x, float y, float z);

protected:
	float pos_x;
	float pos_y;
	float pos_z;
	float speed;
};

