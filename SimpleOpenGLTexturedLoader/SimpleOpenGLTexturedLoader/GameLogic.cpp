#include "GameLogic.h"
#include "CubeModel.h"
#include "PlayingState.h"
#include "TestState.h"
#include "Timer.h"

GameLogic::GameLogic() {
	//ShapeObject playerObject(0, 0, 0, std::make_shared<CubeShape>(CubeShape(1)));
	/*player = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, std::make_shared<CubeShape>(CubeShape(1)), 0.25));
	objects.push_back(std::shared_ptr<GameObject>(player));*/
    setState(State::PLAYING);
    keyBuffer = '_';
}
void GameLogic::display() {
    getCurrentState()->display();
}

void GameLogic::update() {
    getCurrentState()->update();
}

void GameLogic::setCamera() {
    getCurrentState()->setCamera();
}

void GameLogic::setPerspective(bool setModelView)
{
    if(getCurrentState()) //check for not null
        getCurrentState()->setPerspective(setModelView);
}

//void GameLogic::setCamera() {
//    getCurrentState()->setCamera();
//}

void GameLogic::handleInput(unsigned char key, int x, int y){
    getCurrentState()->handleInput(key, x, y);
}

void GameLogic::handleInputUp(unsigned char key, int x, int y) {
    getCurrentState()->handleInputUp(key, x, y);
}

void GameLogic::pushState(State state) {
    switch (state) {

        //emplace new state on top of the stack based on function parameters

    case State::PLAYING:
        states.emplace(new PlayingState(this));
        break;

    case State::TEST:
        states.emplace(new TestState(this));
        break;

    default:
        states.emplace(new TestState(this));
        break;
    }
    setPerspective();

}

void GameLogic::popState() {
    delete(states.top());
    states.pop();
    setPerspective();
}

void GameLogic::setState(State state) {

    if (!states.empty())
        popState();

    pushState(state); //push new state on top of stack
    setPerspective();
}

GameState* GameLogic::getCurrentState() const {
	if (!states.empty())
		return states.top(); //get the state on top of the stack

	else
		return nullptr;
}
