#pragma once
#include "ShapeObject.h"
#include <vector>
class CompositeObject : GameObject
{
public:
	//an object made of multiple objects
	explicit CompositeObject(ShapeObject core);
	explicit CompositeObject(ShapeObject core, std::vector<ShapeObject> secondaryObjects);
	explicit CompositeObject(std::vector<ShapeObject> objects);
	void addObject(ShapeObject obj);
	void display() override;
	void update() override;
	void move(float spd = 0);
	void revertMovement(bool x = true, bool y = true, bool z = true);
private:
	ShapeObject coreObject;
	std::vector<ShapeObject> allObjects;


};

