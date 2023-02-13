#pragma once
#include "ShapeObject.h"
#include "PlayerObject.h"
#include <memory>

enum class CollectibleBehaviour {
    POINT, DAMAGE, SWORD, HEART, WINGS
};

class CollectibleObject :
    public ShapeObject
{
public:
    explicit CollectibleObject(float x, float y, float z, std::shared_ptr<Model> _shape, float speed, CollectibleBehaviour behaviour);

    void applyEffect(PlayerObject* player);

    CollectibleBehaviour getCollType() {
        return behaviour;
    }

private:
    CollectibleBehaviour behaviour;
};

