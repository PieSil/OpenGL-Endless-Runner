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
#define POWER_PROB POINT_PROB * STREAK_PROB * STREAK_POWER_PROB //this ensures that probability of spawning a powerup is always the same regardless if it spawns in a streak or bi itself
#define MAX_RAND_VALUE 100
#define DELTA_Z 3
#define DELTA_X -3
#define SPAWN_POS_Z 40
#define SPAWN_INIT_X 6
#define MAX_POINT_STREAK_LENGTH 8
#define MAX_SPIKE_STREAK_LENGTH 4

CollectibleSpawner::CollectibleSpawner() {
	std::srand(std::time(nullptr));
	//collectibleDims = ObjectDimensions();
	//groundDims = ObjectDimensions();

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
					//	// with p = 0.33 it's 1
					//	collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POWER1_ID)), COL_SPEED, CollectibleBehaviour::POWERUP1));
					//}
					//else if (random < 0.66 * MAX_RAND_VALUE) {
					//	// with p = 0.33 it's 2
					//	collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POWER2_ID)), COL_SPEED, CollectibleBehaviour::POWERUP2));
					//}
					//else {
					//	// with p = 0.33 it's 3
					//	collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POWER3_ID)), COL_SPEED, CollectibleBehaviour::POWERUP3));
					//}
				}

				else if (random < (POWER_PROB + SPIKE_PROB) * MAX_RAND_VALUE) {
					//with p = 0.4 it's an obstacle 

					//decide whether to spawn a single collectible or a streak


					//TODO FIX THIS
					random = std::rand() % MAX_RAND_VALUE;
					if (random < STREAK_PROB * MAX_RAND_VALUE) {
						//setup streak
						//collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(SPIKEBALL_ID)), COL_SPEED, CollectibleBehaviour::DAMAGE));
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
						//collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(SPIKEBALL_ID)), COL_SPEED, CollectibleBehaviour::DAMAGE));
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

		//	auto random = std::rand() % MAX_RAND_VALUE;
		//	if (collectibleAllowed && random < COLL_PROB * MAX_RAND_VALUE) {
		//		//with p = 0.4 place a collectible
		//		random = std::rand() % MAX_RAND_VALUE;
		//		if (random < MAX_RAND_VALUE * POWER_PROB) {
		//			//with p = 0.2 it's a power up
		//			random = std::rand() % MAX_RAND_VALUE;
		//			if (random < 0.33 * MAX_RAND_VALUE) {
		//				// with p = 0.33 it's 1
		//				collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POWER1_ID)), COL_SPEED, CollectibleBehaviour::POWERUP1));
		//			}
		//			else if (random < 0.66 * MAX_RAND_VALUE) {
		//				// with p = 0.33 it's 2
		//				collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POWER2_ID)), COL_SPEED, CollectibleBehaviour::POWERUP2));
		//			}
		//			else {
		//				// with p = 0.33 it's 3
		//				collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POWER3_ID)), COL_SPEED, CollectibleBehaviour::POWERUP3));
		//			}
		//		}
		//		else if (random < (POWER_PROB + SPIKE_PROB) * MAX_RAND_VALUE) {
		//			//with p = 0.4 it's an obstacle 

		//			//TODO check if previous N positions are all occupied by an obstacle, if yes do not place an obstacle, N = MAX_SPIKES_IN_ROW
		//			if (collectibleAllowed) {
		//				collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(SPIKEBALL_ID)), COL_SPEED, CollectibleBehaviour::DAMAGE));
		//			}
		//		}
		//		else {
		//			//with P = 0.4 it's a point
		//			collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POINT_SPHERE_ID)), COL_SPEED, CollectibleBehaviour::POINT));

		//		}
		//		//place collectible
		//		if (collectibleAllowed) {
		//			collectible->incrZSpeed(-1);
		//			collectibles.push_back(collectible);
		//		}
		//		else {
		//		}
		//	}
		//	else {

		//	}
		//}
		//return collectibles;
	//}

std::list<std::shared_ptr<CollectibleObject>> CollectibleSpawner::getCollectibles(aiVector3D playerPos, aiVector3D groundPos, bool considerPlayerPos) {
	////TODO optimize
	auto collectibles = std::list<std::shared_ptr<CollectibleObject>>();
	//int deltaPLayerZ = 0;

	//if (collectibleDims.maxArea == 0) {
	//	collectibleDims = getMaxCollectibleDim();
	//}

	//if (groundDims.maxArea == 0) {
	//	groundDims = getGroundDim();
	//}

	//// set distance between center of objects, there must be at least N units of space between the borders of two contiguous objects, for now N = 1
	//float deltaX = collectibleDims.maxX+1;
	//float deltaZ = collectibleDims.maxZ + 2;

	//if (considerPlayerPos) {
	//	deltaPLayerZ = 3 * deltaZ;
	//}

	////divide ground in a grid, each cell may or may not hold a collectible
	//int slotsAlongX = int(groundDims.maxX / deltaX);
	//int slotsAlongZ = int((groundDims.maxZ - deltaPLayerZ) / deltaZ);

	//int** grid = new int* [slotsAlongZ];
	//if (slotsAlongZ)
	//{
	//	grid[0] = new int[slotsAlongZ * slotsAlongX];
	//	for (int i = 1; i < slotsAlongZ; ++i)
	//		grid[i] = grid[0] + i * slotsAlongX;
	//}

	////set base spawn point of a collectible as the middle point of the cell with minimum X and Y 
	//float minX = (groundPos.x - (groundDims.maxX/2)) + deltaX;
	//float minZ = deltaZ / 2;

	////determine total number of cells the ground was divided into
	//int totalSlots = slotsAlongX * slotsAlongZ;

	//bool collectibleAllowed; //flag variable to check if collectible can be placed in a specific position

	////iterate over all slots, for each of them decide whether to place a collectible (and which kind of collectible) or not
	//for (int slotZ = 0; slotZ < slotsAlongZ; slotZ++) {
	//	for (int slotX = 0; slotX < slotsAlongX; slotX++) {
	//		//std::srand(static_cast<unsigned int>(std::time(nullptr)));
	//		collectibleAllowed = true;

	//		float posX = (minX + deltaX * slotX) + groundPos.x; //compute slot X position
	//		float posZ = (minZ + deltaZ * slotZ) + groundPos.z; //compute slot Z position

	//		//determine if collectible would spawn too close to the player, in that case do not spawn collectible
	//		if (deltaPLayerZ + playerPos.z >= posZ) {
	//			collectibleAllowed = false;
	//		}

	//		auto random = std::rand() % MAX_RAND_VALUE;
	//		if (collectibleAllowed && random < COLL_PROB * MAX_RAND_VALUE) {
	//			std::shared_ptr<CollectibleObject> collectible;
	//			//with p = 0.4 place a collectible
	//			random = std::rand() % MAX_RAND_VALUE; 
	//			if (random < MAX_RAND_VALUE * POWER_PROB) {
	//				//with p = 0.2 it's a power up
	//				grid[slotZ][slotX] = POWER;
	//				random = std::rand() % MAX_RAND_VALUE;
	//				if (random < 0.33 * MAX_RAND_VALUE) {
	//					// with p = 0.33 it's 1
	//					collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POWER1_ID)), 5, CollectibleBehaviour::POWERUP1));
	//				} else if (random < 0.66 * MAX_RAND_VALUE) {
	//					// with p = 0.33 it's 2
	//					collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POWER2_ID)), 5, CollectibleBehaviour::POWERUP2));
	//				} else {
	//					// with p = 0.33 it's 3
	//					collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POWER3_ID)), 5, CollectibleBehaviour::POWERUP3));
	//				}
	//			}
	//			else if (random < (POWER_PROB + SPIKE_PROB)*MAX_RAND_VALUE) {
	//				//with p = 0.4 it's an obstacle 

	//				//check if previous N positions are all occupied by an obstacle, if yes do not place an obstacle, N = MAX_SPIKES_IN_ROW
	//				int i = 0;
	//				collectibleAllowed = false;
	//				while (!collectibleAllowed && i < MAX_SPIKES_IN_ROW) {

	//					//as soon as you find a slot not occupied by a spike stop iterating
	//					if (slotZ >= (i+1) && grid[slotZ - (i+1)][slotX] != SPIKE) {
	//						collectibleAllowed = true;
	//					}
	//					i++;
	//				}
	//				if (collectibleAllowed) {
	//					grid[slotZ][slotX] = SPIKE;
	//					collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(SPIKEBALL_ID)), 5, CollectibleBehaviour::DAMAGE));
	//				}
	//			}
	//			else {
	//				//with P = 0.4 it's a point
	//				grid[slotZ][slotX] = POINT_COLL;
	//				collectible = std::make_shared<CollectibleObject>(CollectibleObject(posX, 0, posZ, std::make_shared<AssimpModel>(AssimpModel(POINT_SPHERE_ID)), 5, CollectibleBehaviour::POINT));
	//				
	//			}
	//			//place collectible
	//			if (collectibleAllowed) {
	//				collectible->incrZSpeed(-1);
	//				collectibles.push_back(collectible);
	//			}
	//			else {
	//				grid[slotZ][slotX] = EMPTY;
	//			}
	//		}
	//		else {
	//			//else place 0 into grid[slotZ][slotX]
	//			grid[slotZ][slotX] = EMPTY;

	//		}
	//	}
	//}

	//if (slotsAlongZ) delete[] grid[0];
	//delete[] grid;

	return collectibles;

}


//ObjectDimensions CollectibleSpawner::getMaxCollectibleDim() {
//	auto point = std::make_shared<CollectibleObject>(CollectibleObject(0, 0, 0, std::make_shared<AssimpModel>(AssimpModel(POINT_SPHERE_ID)), 5, CollectibleBehaviour::POINT));
//	auto spike = std::make_shared<CollectibleObject>(CollectibleObject(0, 0, 0, std::make_shared<AssimpModel>(AssimpModel(SPIKEBALL_ID)), 5, CollectibleBehaviour::DAMAGE));
//	auto power = std::make_shared<CollectibleObject>(CollectibleObject(0, 0, 0, std::make_shared<AssimpModel>(AssimpModel(POWER1_ID)), 5, CollectibleBehaviour::SWORD));
//
//	aiVector3D* pointMin = new aiVector3D(0, 0, 0);
//	aiVector3D* pointMax = new aiVector3D(0, 0, 0);
//
//	aiVector3D* spikeMin = new aiVector3D(0, 0, 0);
//	aiVector3D* spikeMax = new aiVector3D(0, 0, 0);
//
//	aiVector3D* powerMin = new aiVector3D(0, 0, 0);
//	aiVector3D* powerMax = new aiVector3D(0, 0, 0);
//
//	point->getHitbox(pointMin, pointMax);
//	spike->getHitbox(spikeMin, spikeMax);
//	power->getHitbox(powerMin, powerMax);
//
//	float pointX = abs(pointMax->x - pointMin->x);
//	float pointY = abs(pointMax->y - pointMin->y);
//	float pointZ = abs(pointMax->z - pointMin->z);
//
//	float spikeX = abs(spikeMax->x - spikeMin->x);
//	float spikeY = abs(spikeMax->y - spikeMin->y);
//	float spikeZ = abs(spikeMax->z - spikeMin->z);
//
//	float powerX = abs(powerMax->x - powerMin->x);
//	float powerY = abs(powerMax->y - powerMin->y);
//	float powerZ = abs(powerMax->z - powerMin->z);
//
//	float maxX = pointX;
//	float maxY = pointY;
//	float maxZ = pointZ;
//
//	//find max for each of the 3 dimensions
//
//	if (spikeX > maxX) {
//		maxX = spikeX;
//	}
//
//	if (powerX > maxX) {
//		maxX = powerX;
//	}
//
//	if (spikeY > maxY) {
//		maxY = spikeY;
//	}
//
//	if (powerY > maxY) {
//		maxY = powerY;
//	}
//
//	if (spikeZ > maxZ) {
//		maxZ = spikeZ;
//	}
//
//	if (powerZ > maxZ) {
//		maxZ = powerZ;
//	}
//
//	delete pointMin;
//	delete pointMax;
//
//	delete spikeMin;
//	delete spikeMax;
//
//	delete powerMin;
//	delete powerMax;
//
//	//create struct that holds info about max height, width, depth, area (along XZ plane) and volume a collectible may have
//	return ObjectDimensions(maxX, maxY, maxZ, maxX * maxZ, maxX * maxZ * maxY);
//}

ObjectDimensions CollectibleSpawner::getGroundDim() {
	auto ground = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, std::make_shared<AssimpModel>(AssimpModel(GROUND_ID))));

	aiVector3D* min = new aiVector3D(0, 0, 0);
	aiVector3D* max = new aiVector3D(0, 0, 0);

	ground->getHitbox(min, max);

	float x = abs(max->x - min->x);
	float y = abs(max->y - min->y);
	float z = abs(max->z - min->z);

	delete min;
	delete max;

	return ObjectDimensions(x, y, z, x * z, x * y * z);
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
	
	CollectibleObject collectible = CollectibleObject(posX, posY, posZ, ModelRepository::getModel(CROSS_ID), CollectibleBehaviour::DAMAGE, COL_SPEED);
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
