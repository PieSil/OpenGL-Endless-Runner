#include "CompositeObject.h"

CompositeObject::CompositeObject(ShapeObject core) : GameObject(core.getPosx(), core.getPosy(), core.getPosz(), core.getSpeed()), coreObject(core) {
	addObject(core);
}

CompositeObject::CompositeObject(ShapeObject core, std::vector<ShapeObject> secondaryObjects) : GameObject(core.getPosx(), core.getPosy(), core.getPosz(), core.getSpeed()), coreObject(core) {
	addObject(core);
	for (auto obj : secondaryObjects) {
		allObjects.push_back(obj);
	}

}

CompositeObject::CompositeObject(std::vector<ShapeObject> objects) : GameObject(objects[0].getPosx(), objects[0].getPosy(), objects[0].getPosz(), objects[0].getSpeed()), coreObject(objects[0])
{
	for (auto obj : objects) {
		allObjects.push_back(obj);
	}
	
}

void CompositeObject::addObject(ShapeObject obj) {
	allObjects.push_back(obj);
}

void CompositeObject::display()
{
	for (auto obj : allObjects) {
		obj.display();
	}
}

void CompositeObject::update()
{
	for (auto obj : allObjects) {
		obj.update();
	}
}

void CompositeObject::move(float spd)
{
	for (auto obj : allObjects) {
		obj.move(spd);
	}
}

void CompositeObject::revertMovement(bool x, bool y, bool z)
{
	for (auto obj : allObjects) {
		obj.revertMovement(x, y, z);
	}
}
