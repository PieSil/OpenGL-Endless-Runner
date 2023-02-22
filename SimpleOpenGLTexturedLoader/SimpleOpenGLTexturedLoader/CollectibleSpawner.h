#pragma once
#include "CollectibleObject.h"
#include "Const.h"
#include <list>
#define SLOTS_ALONG_Z 5

enum SlotStatus {
	FREE, DAMAGE_ROW, POINT_ROW, EMPTY_ROW
};

struct SlotMemory {

	SlotMemory() {
		powerGenerated = false;
		status = SlotStatus::FREE;
		count = 0;
		streakLength = 0;
	}


	SlotMemory(SlotStatus status, int streakLength) : status(status), streakLength(streakLength) {
		count = 0;
		powerGenerated = false;
	}

	~SlotMemory() {};

	bool powerGenerated;
	int count;
	int streakLength;
	SlotStatus status;
};

class CollectibleSpawner {
public:
	explicit CollectibleSpawner();
	~CollectibleSpawner();
	std::list<std::shared_ptr<CollectibleObject>> spawnCollectibles();
	std::list<std::shared_ptr<CollectibleObject>> getCollectibles(aiVector3D playerPos, aiVector3D groundPos, bool considerPlayerPos = false);
	std::list<std::shared_ptr<CollectibleObject>> getCollectibleRow();

	CollectibleObject getPoint(float posX, float posY, float posZ);
	CollectibleObject getDamage(float posX, float posY, float posZ);	
	CollectibleObject getPowerup(float posX, float posY, float posZ, float randomValue = -1);

private:
	double elapsedSinceLastSpawn;
	SlotMemory slotMemory[SLOTS_ALONG_Z];
};

