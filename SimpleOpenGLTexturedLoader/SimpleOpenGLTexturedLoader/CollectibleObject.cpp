#include "CollectibleObject.h"
#include "Context.h"
#include "AudioPlayer.h"
#include <iostream>

CollectibleObject::CollectibleObject(float x, float y, float z, std::shared_ptr<Model> _shape, CollectibleBehaviour behaviour, float speed, aiVector3D scale) : ShapeObject(x, y, z, _shape, scale, speed), behaviour(behaviour) {
	shape = std::shared_ptr<Model>(_shape);
}

bool CollectibleObject::applyEffect(PlayerObject* player) {
	//applies collectible effect to player or context
	bool result = true; //returns true if collectible should be destoyed

	switch (behaviour) {
	case CollectibleBehaviour::POINT:
		Context::getContext()->incrScore(1);
		AudioPlayer::playSound(RUPEE_SOUND);
		//std::cout << "Score: " << Context::getContext()->getScore() << "\n";
		break;
	case CollectibleBehaviour::DAMAGE:
		if (!player->isInvincible()) {
			player->incrLives(-1);
			//std::cout << "Player lives: " << player->getLives() << "\n";
			player->setInvincible(true);
		}
		else {
			result = false;
		}
		break;
	case CollectibleBehaviour::SWORD:
		player->setShootActive(true);
		AudioPlayer::playSound(SWORD_SOUND);
		break;
	case CollectibleBehaviour::HEART:
		if (player->getLives() >= 3) {
			Context::getContext()->incrScore(1);
		}
		else {
			player->incrLives(1);
		}
		//std::cout << "Player lives: " << player->getLives() << "\n";
		break;
	case CollectibleBehaviour::WINGS:
		player->setFlightActive(true);
		AudioPlayer::playSound(SWORD_SOUND);
		break;
	default:
		break;
	}

	return result;
}
