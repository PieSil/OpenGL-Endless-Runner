#include "CollectibleSpawner.h"
#include "AssimpModel.h"
#include "Timer.h"
#include "Context.h"
#include "ModelRepository.h"
#include <math.h>
#include <cstdlib>
#include <ctime>

#define EMPTY 0
#define POINT_COLL 1
#define SPIKE 2
#define POWER 3
#define COLL_PROB 0.2
#define POINT_PROB 0.2
#define SPIKE_PROB 0.6
#define STREAK_PROB 0.9 
#define STREAK_POWER_PROB 0.01
#define POWER_PROB POINT_PROB * STREAK_PROB * STREAK_POWER_PROB //this ensures that probability of spawning a powerup is always the same regardless if it spawns in a streak or by itself
#define MAX_RAND_VALUE 100
#define DELTA_Z 3
#define DELTA_X -3
#define SPAWN_POS_Z COL_SPAWN_Z
#define SPAWN_INIT_X 6
#define MAX_POINT_STREAK_LENGTH 8
#define MAX_SPIKE_STREAK_LENGTH 4

CollectibleSpawner::CollectibleSpawner() {
	std::srand(std::time(nullptr));

	elapsedSinceLastSpawn = 0;
	for (int i = 0; i < SLOTS_ALONG_Z; i++) {
		slotMemory[i] = SlotMemory();
	}
	
}

	CollectibleSpawner::~CollectibleSpawner() {
		//delete[] slotMemory;
	};

std::list<std::shared_ptr<CollectibleObject>> CollectibleSpawner::spawnCollectibles() {
	auto collectibles = std::list<std::shared_ptr<CollectibleObject>>();
	elapsedSinceLastSpawn += Timer::getTimer()->getElapsed();
	if (Context::getContext()->getGameSpeed() * elapsedSinceLastSpawn >= DELTA_Z) {
		collectibles = getCollectibleRow();
		elapsedSinceLastSpawn = 0;
	}

	return collectibles;
}

std::list<std::shared_ptr<CollectibleObject>> CollectibleSpawner::getCollectibleRow() {

	/*
	* RULES FOR COLLECTIBLE GENERATION
	* Each slot can generate a single collectible or a streak of collectibles
	* PowerUps cannot be generated in streaks
	* If a slot is currently generating a streak of collectibles do not overwrite the streak
	* A streak of point collectibles may contain at most 1 PowerUp
	* A minimum of N Free slots should be generated after any kind of Spike collectible streak, for now N = 2
	*/

	auto collectibles = std::list<std::shared_ptr<CollectibleObject>>();
	for (int i = 0; i < SLOTS_ALONG_Z; i++) {
		bool collectibleGenerated = false;
		float posX = SPAWN_INIT_X + i * DELTA_X;
		float posY = 0;
		float posZ = SPAWN_POS_Z;
		//auto currentSlotMemory = slotMemory[i];
		std::shared_ptr<CollectibleObject> collectible;
		auto random = std::rand() % MAX_RAND_VALUE;

		//First check if current slot holds a row
		if (slotMemory[i].status == SlotStatus::DAMAGE_ROW) {
			collectible = std::make_shared<CollectibleObject>(getDamage(posX, posY, posZ));
			collectibleGenerated = true;

			//increment streak count
			slotMemory[i].count++;

			//if length of streak has been reached set an "empty" streak slot memory
			if (slotMemory[i].count >= slotMemory[i].streakLength) {
				slotMemory[i].count = 0;
				slotMemory[i].status = EMPTY_ROW;
				slotMemory[i].streakLength = 2;
				slotMemory[i].powerGenerated = false;
			}
		}
		else if (slotMemory[i].status == SlotStatus::POINT_ROW) {

			random = std::rand() % MAX_RAND_VALUE;

			//if it's a streak of points check if PowerUp was generated, if not generate it with a very low probability
			if (!slotMemory[i].powerGenerated && random < STREAK_POWER_PROB * MAX_RAND_VALUE) {

				collectible = std::make_shared<CollectibleObject>(getPowerup(posX, posY, posZ));
				collectibleGenerated = true;
				slotMemory[i].powerGenerated = true;
			}
			else {
				//if power is not generated, generate a point instead
				collectible = std::make_shared<CollectibleObject>(getPoint(posX, posY, posZ));
				collectibleGenerated = true;
			}


			//increment streak count
			slotMemory[i].count++;

			//if length of streak has been reached reset slot memory
			if (slotMemory[i].count >= slotMemory[i].streakLength) {
				slotMemory[i] = SlotMemory();
			}
		}
		else if (slotMemory[i].status == SlotStatus::EMPTY_ROW) {
			collectibleGenerated = false;

			//increment streak count
			slotMemory[i].count++;

			//if length of streak has been reached reset slot memory
			if (slotMemory[i].count >= slotMemory[i].streakLength) {
				slotMemory[i] = SlotMemory();
			}
		}
		else {
			//if current slot does not hold a row determine what to spawn in that slot (nothing, a single collectible, a row)

			random = std::rand() % MAX_RAND_VALUE;
			if (random < COLL_PROB * MAX_RAND_VALUE) {
				//with p = 0.4 place a collectible
				collectibleGenerated = true;
				random = std::rand() % MAX_RAND_VALUE;
				if (random < MAX_RAND_VALUE * POWER_PROB) {
					//with p = 0.2 it's a power up
					collectible = std::make_shared<CollectibleObject>(getPowerup(posX, posY, posZ));
				}

				else if (random < (POWER_PROB + SPIKE_PROB) * MAX_RAND_VALUE) {
					//with p = 0.4 it's an obstacle 

					//decide whether to spawn a single collectible or a streak


					//TODO FIX THIS
					random = std::rand() % MAX_RAND_VALUE;
					if (random < STREAK_PROB * MAX_RAND_VALUE) {
						//setup streak
						slotMemory[i].count = 1;
						slotMemory[i].status = DAMAGE_ROW;
						slotMemory[i].streakLength = (std::rand() % (MAX_SPIKE_STREAK_LENGTH - 2)) + 2; //randomly determine streak length between 2 and MAX_SPIKE_STREAK_LENGTH
					}
					//spawn single spike
					collectible = std::make_shared<CollectibleObject>(getDamage(posX, posY, posZ));

				}
				else {
					//with p = 0.4 it's a point
					random = std::rand() % MAX_RAND_VALUE;
					if (random < STREAK_PROB * MAX_RAND_VALUE) {
						//setup streak
						slotMemory[i].count = 1;
						slotMemory[i].status = POINT_ROW;
						slotMemory[i].streakLength = (std::rand() % (MAX_POINT_STREAK_LENGTH - 2)) + 2; //randomly determine streak length between 2 and MAX_SPIKE_STREAK_LENGTH
					}
					//spawn single point
					collectible = std::make_shared<CollectibleObject>(getPoint(posX, posY, posZ));

				}
			}


		}

		if (collectibleGenerated) {
			collectible->incrZSpeed(-1);
			collectibles.push_back(collectible);
		}
	}


	return collectibles;
}


std::list<std::shared_ptr<CollectibleObject>> CollectibleSpawner::getCollectibles(aiVector3D playerPos, aiVector3D groundPos, bool considerPlayerPos) {
	auto collectibles = std::list<std::shared_ptr<CollectibleObject>>();

	return collectibles;

}

CollectibleObject CollectibleSpawner::getPoint(float posX, float posY, float posZ)
{
	//randomly choose one model
	auto modelId = RUPEE_GREEN_ID + std::rand() % (RUPEE_PURPLE_ID-RUPEE_GREEN_ID);
	CollectibleObject collectible = CollectibleObject(posX, posY, posZ, ModelRepository::getModel(modelId), CollectibleBehaviour::POINT, COL_SPEED);
	return collectible;
}

CollectibleObject CollectibleSpawner::getDamage(float posX, float posY, float posZ)
{
	
	CollectibleObject collectible = CollectibleObject(posX, posY, posZ, ModelRepository::getModel(SPIKES_ID), CollectibleBehaviour::DAMAGE, COL_SPEED);
	return collectible;
}

CollectibleObject CollectibleSpawner::getPowerup(float posX, float posY, float posZ, float randomValue)
{
	//CollectibleObject collectible = NULL;
	if (randomValue < 0) {
		randomValue = std::rand() % MAX_RAND_VALUE;
	}
	//with p = 0.2 it's a power up
	if (randomValue < 0.33 * MAX_RAND_VALUE) {
		// with p = 0.33 it's 1
		return CollectibleObject(posX, posY, posZ, ModelRepository::getModel(SWORD_POWERUP_ID), CollectibleBehaviour::SWORD, COL_SPEED);
	}
	else if (randomValue < 0.66 * MAX_RAND_VALUE) {
		// with p = 0.33 it's 2
		return CollectibleObject(posX, posY, posZ, ModelRepository::getModel(HEART_ID), CollectibleBehaviour::HEART, COL_SPEED);
	}
	else {
		// with p = 0.33 it's 3
		return CollectibleObject(posX, posY, posZ, ModelRepository::getModel(ZELDALOGO_ID), CollectibleBehaviour::WINGS, COL_SPEED);
	}
}
