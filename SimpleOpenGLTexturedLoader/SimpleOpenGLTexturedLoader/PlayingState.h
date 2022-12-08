#include <memory>
#include <iostream>
#include <list>
#include <stack>
#include "GameState.h"
//#include "GameLevel.h"

class PlayingState : public  GameState {

public:

    explicit PlayingState(GameLogic* game);

    ~PlayingState() {};

    void handleInput(unsigned char key) override;

private:
    std::shared_ptr<GameObject> player;
    //GameLevel level;
};


