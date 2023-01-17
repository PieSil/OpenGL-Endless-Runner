#pragma once
#include "ShapeObject.h"
//an object subjected to laws of physics (falls if not on ground)

class PlayerObject :
    public ShapeObject {

public:
    explicit PlayerObject(float x, float y, float z, std::shared_ptr<Model> _shape, float speed = 1);
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

    int getLives() {
        return lives;
    }

    void incrLives(int value) {
        lives += value;
        if (lives < 0) {
            lives = 0;
        }
    }

    void setInputRecorded(bool value) {
        inputRecorded = value;
    }

    bool isInputRecorded() {
        return inputRecorded;
    }

protected:
    bool onGround;
    float jumpSpeed;
    int lives;
    bool inputRecorded;
};

