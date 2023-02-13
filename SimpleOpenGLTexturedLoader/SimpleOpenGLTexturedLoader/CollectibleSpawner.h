#pragma once
#include "CollectibleObject.h"
#include "Const.h"
#include <list>
#define SLOTS_ALONG_Z 5

enum SlotStatus {
	FREE, SPIKE_ROW, POINT_ROW, EMPTY_ROW
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

struct ObjectDimensions {

	ObjectDimensions() : maxZ(0), maxX(0), maxY(0), maxArea(0), maxVolume(0) {}
	ObjectDimensions(float x, float y, float z, float area, float volume) : maxX(x), maxY(y), maxZ(z), maxArea(area), maxVolume(volume) {}
	float maxZ;
	float maxX;
	float maxY;
	float maxArea;
	float maxVolume;
};

class CollectibleSpawner {
public:
	explicit CollectibleSpawner();
	~CollectibleSpawner();
	std::list<std::shared_ptr<CollectibleObject>> spawnCollectibles();
	std::list<std::shared_ptr<CollectibleObject>> getCollectibles(aiVector3D playerPos, aiVector3D groundPos, bool considerPlayerPos = false);
	std::list<std::shared_ptr<CollectibleObject>> getCollectibleRow();
	//ObjectDimensions getMaxCollectibleDim();
	ObjectDimensions getGroundDim();

	CollectibleObject getPoint(float posX, float posY, float posZ);
	CollectibleObject getDamage(float posX, float posY, float posZ);	
	CollectibleObject getPowerup(float posX, float posY, float posZ, float randomValue = -1);

private:
	ObjectDimensions collectibleDims;
	ObjectDimensions groundDims;
	double elapsedSinceLastSpawn;
	SlotMemory slotMemory[SLOTS_ALONG_Z];
};

