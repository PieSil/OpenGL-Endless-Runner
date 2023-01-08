#pragma once
#include "GameState.h"

//A GameState derived class, used to test the correct behaviour of state stack in GameLogic class

class TestState :
    public GameState {
public:

    explicit TestState(GameLogic* game);

    ~TestState() {};

    void handleInput(unsigned char key, int x, int y) override;
    void handleInputUp(unsigned char key, int x, int y) override {};

private:
    std::shared_ptr<GameObject> player;
    //GameLevel level;
};

