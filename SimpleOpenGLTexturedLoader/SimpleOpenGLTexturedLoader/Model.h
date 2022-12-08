#pragma once
class Model {
public:
	explicit Model();

	virtual void display(float x, float y, float z) = 0;
	virtual void animate() {};
};

