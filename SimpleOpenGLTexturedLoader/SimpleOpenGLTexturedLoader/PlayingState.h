#include <memory>
#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include "GameState.h"
#include "PlayerObject.h"
#include "CollectibleObject.h"
#include "CollectibleSpawner.h"

//The game state which should correspond to the actual game 

class PlayingState : public  GameState {

public:

    explicit PlayingState(GameLogic* game);

    ~PlayingState() {};

    void display() override;
    void update() override;
    void handleInput(unsigned char key, int x, int y) override;
    void handleInputUp(unsigned char key, int x, int y) override;
    void checkCollisions();

    void spawnNewGround();

private:
    std::shared_ptr<PlayerObject> player;
    std::list<std::shared_ptr<ShapeObject>> collidables; //objects to test for collisions
    std::vector<std::shared_ptr<CollectibleObject>> collectibles; //Items in this list MUST NOT be included in GameState "object" list
    //std::shared_ptr<ShapeObject> ground;
    std::vector<std::shared_ptr<ShapeObject>> grounds; //use a vector of "grounds" allows for multiple objects classified and treated as ground
    CollectibleSpawner  collectibleSpawner;
    int pointsToNextAccel;

};


