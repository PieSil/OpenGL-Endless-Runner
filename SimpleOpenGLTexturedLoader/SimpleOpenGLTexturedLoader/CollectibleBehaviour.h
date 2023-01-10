#pragma once
#include "PlayerObject.h"
class CollectibleBehaviour {
public:
	explicit CollectibleBehaviour() {};
	virtual void applyEffect(PlayerObject player) = 0;

private:
};

