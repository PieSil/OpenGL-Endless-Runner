#include "CollectibleObject.h"
#include "Context.h"
#include <iostream>

CollectibleObject::CollectibleObject(float x, float y, float z, std::shared_ptr<Model> _shape, float speed, CollectibleBehaviour behaviour) : ShapeObject(x, y, z, _shape, speed), behaviour(behaviour) {
	shape = std::shared_ptr<Model>(_shape);
}

void CollectibleObject::applyEffect(PlayerObject* player) {
	//applies collectible effect to player or context

	switch (behaviour) {
	case CollectibleBehaviour::POINT:
		Context::getContext()->incrScore(1);
		std::cout << "Score: " << Context::getContext()->getScore() << "\n";
		break;
	default:
		break;
	}
}
