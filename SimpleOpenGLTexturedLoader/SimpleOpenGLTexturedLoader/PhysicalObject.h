#pragma once
#include "ShapeObject.h"
//an object subjected to laws of physics (falls if not on ground)

class PhysicalObject :
    public ShapeObject {

public:
    explicit PhysicalObject(float x, float y, float z, std::shared_ptr<Model> _shape, float speed = 1);
    void update() override;
    void fall();

    bool isOnGround() {
        return onGround;
    }

    void setJumpSpeed(float value) {
        jumpSpeed = value;
    }

    void setOnGround(bool value) {
        onGround = value;
    }

protected:
    bool onGround;
    float jumpSpeed;
};

