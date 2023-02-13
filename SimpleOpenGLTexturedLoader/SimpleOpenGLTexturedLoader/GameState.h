#pragma once
#include <memory>
#include "GameLogic.h"
#include "ModelRepository.h"

//abstract class, represents a state of the game, like menu, playing state, pause, etc. 
//multiple states can be active at once thanks to a stack structure (see GameLogic class)

class GameState {
   
public:
    explicit GameState(GameLogic* game, bool persp = false);

    virtual ~GameState() {};

    virtual void update();
    virtual void handleInput(unsigned char key, int x, int y) = 0;
    virtual void display();
    virtual void handleInputUp(unsigned char key, int x, int y) {};
    void setPerspective(bool useDefault = true, bool setModelView = true, bool perspParam = false);
    void setCamera();

    void addGameObject(float x, float y, float z, std::shared_ptr<Model> shape);

protected:
    //GameLogic* game;
    GameLogic* game; //a pointer to the GameLogic object, this is necessary in order to push/pop/set a state from within another state 
    std::vector<std::shared_ptr<GameObject>> objects; //a list of (pointers to) objects that need to be rendered
    bool persp;
};

