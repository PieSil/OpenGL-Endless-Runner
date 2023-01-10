#pragma once
#include "ShapeObject.h"
#include "CollectibleBehaviour.h"
#include <memory>
class CollectibleObject :
    public ShapeObject
{
public:
    explicit CollectibleObject();

private:
    std::shared_ptr<CollectibleBehaviour> behaviour;
};

