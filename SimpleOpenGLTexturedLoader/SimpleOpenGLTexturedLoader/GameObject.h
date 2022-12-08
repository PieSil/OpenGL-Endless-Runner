#pragma once
#include<list>
#include<vector>

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

