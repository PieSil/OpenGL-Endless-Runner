#pragma once
#include "ShapeObject.h"
#include "Const.h"
#include <iostream>
#include "Timer.h"

enum class PowerupType {
    SHOOT, FLIGHT
};

class PlayerObject :
    public ShapeObject {

public:
    explicit PlayerObject(float x, float y, float z, std::shared_ptr<Model> _shape, aiVector3D scale = aiVector3D(1,1,1), float speed = 1);
    void update() override;
    void display() override;
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
        if (lives > 3) {
            lives = 3;
        }
    }

    void setInputRecorded(bool value) {
        inputRecorded = value;
    }

    bool isInputRecorded() {
        return inputRecorded;
    }

    bool isShootActive() {
        return shootActive;
    }

    void setShootActive(bool value) {
        if (value) { //if power is activated
            shootPowerElapsed = 0;
            shootIntervalElapsed = PROJECTILE_INTERVAL;
        }
        else {
            std::cout << "Power deactivated";
        }
        shootActive = value;
    }

    bool isFlightActive() {
        return flightActive;
    }

    void setFlightActive(bool value) {
        if (value) { //if power is activated
            flightPowerElapsed = 0;
        } else if (!value && !onGround && inputRecorded) { //otherwise if the player is jumping reset its horizontal speed and remove the input flag
            inputRecorded = false;
            resetXSpeed();
        }
        flightActive = value;
    }

    bool shoot();

    void setShooting(bool value) {
        shooting = value;
    }

    bool isShooting() {
        return shooting;
    }

    void setInvincible(bool value) {
        if (value) {
            invicibilityElapsed = 0;
            invicibleDisplayElapsed = INVICIBLE_DISPLAY_INTERVAL;
        }
        else {
            invicibilityElapsed = 0;
            invicibleDisplayElapsed = 0;
        }
        invincible = value;
    }

    bool isInvincible() {
        return invincible;
    }

    float getRemainingTime(PowerupType pwr);

protected:
    float invicibilityElapsed;
    float invicibleDisplayElapsed;
    float shootPowerElapsed;
    float shootIntervalStart;
    float shootIntervalElapsed;
    float flightPowerElapsed;
    float jumpSpeed;
    int lives;
    bool onGround;
    bool inputRecorded;
    bool shootActive;
    bool flightActive;
    bool shooting;
    bool invincible;
};

