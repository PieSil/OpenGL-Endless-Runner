#include <memory>
#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include "GameState.h"
#include "PlayerObject.h"
#include "CollectibleObject.h"
#include "CollectibleSpawner.h"

//The game state which should correspond to the actual game 

struct GroundStruct {
    //keeps a pointer to a ground "piece"
    //also keeps a record of pointers to "side" object associated to a specific ground "piece"
    //these pointers are used to recover and delete these "side" objects when the corresponding ground is deleted

    GroundStruct(std::shared_ptr<ShapeObject> ground, std::shared_ptr<ShapeObject> lborder, std::shared_ptr<ShapeObject> rborder, std::shared_ptr<ShapeObject> linvisible, std::shared_ptr<ShapeObject> rinvisible) {
        this->ground = ground;
        this->lborder = lborder;
        this->rborder = rborder;
        this->linvisible = linvisible;
        this->rinvisible = rinvisible;
    }

    std::shared_ptr<ShapeObject> ground;
    std::shared_ptr<ShapeObject> lborder;
    std::shared_ptr<ShapeObject> rborder;
    std::shared_ptr<ShapeObject> linvisible;
    std::shared_ptr<ShapeObject> rinvisible;

};

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
    void deleteGround(GroundStruct ground);
    void spawnProjectile();

private:
    std::shared_ptr<PlayerObject> player;
    std::vector<std::shared_ptr<ShapeObject>> collidables; //objects to test for collisions
    std::vector<std::shared_ptr<CollectibleObject>> collectibles; //Items in this list MUST NOT be included in GameState "object" list
    //std::shared_ptr<ShapeObject> ground;
    std::vector<GroundStruct> grounds; //use a vector of "grounds" allows for multiple objects classified and treated as ground
    std::vector<std::shared_ptr<ShapeObject>> projectiles;
    CollectibleSpawner  collectibleSpawner;
    int pointsToNextAccel;

};


