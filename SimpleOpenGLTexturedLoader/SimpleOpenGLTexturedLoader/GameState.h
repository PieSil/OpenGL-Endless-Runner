#pragma once
#include <memory>
#include "GameLogic.h"
class GameState {
    //abstract class, represents a state of the game, like menu, playing state, paue, etc. 
    //multiple states can be active at once thanks to a stack structure (see GameLogic class)
public:
    explicit GameState(GameLogic* game);

    virtual ~GameState() {};

    void update();
    virtual void handleInput(unsigned char key) = 0;
    void display();
    void setCamera();

    void addGameObject(float x, float y, float z, std::shared_ptr<Model> shape);

protected:
    //GameLogic* game;
    GameLogic* game; //a pointer to the GameLogic object, this is necessary in order to push/pop/set a state from within another state 
    std::vector<std::shared_ptr<GameObject>> objects; //a list of (pointers to) objects that need to be rendered

};

