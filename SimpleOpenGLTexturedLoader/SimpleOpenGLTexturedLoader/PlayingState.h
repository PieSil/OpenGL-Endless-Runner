#include <memory>
#include <iostream>
#include <list>
#include <stack>
#include "GameState.h"
#include "PlayerObject.h"

//The game state which should correspond to the actual game 

class PlayingState : public  GameState {

public:

    explicit PlayingState(GameLogic* game);

    ~PlayingState() {};

    void update() override;
    void handleInput(unsigned char key, int x, int y) override;
    void handleInputUp(unsigned char key, int x, int y) override;
    void checkCollisions();

private:
    std::shared_ptr<PlayerObject> player;
    std::list<std::shared_ptr<ShapeObject>> collidables; //objects to test for collisions
    std::shared_ptr<ShapeObject> ground;
    //GameLevel level;
};


