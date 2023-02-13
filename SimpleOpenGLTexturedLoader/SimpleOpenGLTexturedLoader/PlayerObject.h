#pragma once
#include "ShapeObject.h"
#include "Const.h"

enum class PowerupType {
    SHOOT, FLIGHT
};

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

    void setShootActive(bool value) {
        if (value) { //if power is activated
            shootPowerStart = glutGet(GLUT_ELAPSED_TIME);
            shootPowerElapsed = 0;
            shootIntervalElapsed = PROJECTILE_INTERVAL;
            shootIntervalStart = glutGet(GLUT_ELAPSED_TIME);
        }
        shootActive = value;
    }

    void setFlightActive(bool value) {
        if (value) { //if power is activated
            flightPowerStart = glutGet(GLUT_ELAPSED_TIME);
            flightPowerElapsed = 0;
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

    float getRemainingTime(PowerupType pwr);

protected:
    float shootPowerStart;
    float flightPowerStart;
    float shootPowerElapsed;
    float shootIntervalStart;
    float shootIntervalElapsed;
    float flightPowerElapsed;
    bool onGround;
    float jumpSpeed;
    int lives;
    bool inputRecorded;
    bool shootActive;
    bool flightActive;
    bool shooting;
};

