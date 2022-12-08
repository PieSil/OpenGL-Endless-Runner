#pragma once
#include "GameState.h"
class TestState :
    public GameState {
public:

    explicit TestState(GameLogic* game);

    ~TestState() {};

    void handleInput(unsigned char key) override;

private:
    std::shared_ptr<GameObject> player;
    //GameLevel level;
};

