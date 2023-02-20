#include "GameLogic.h"
#include "CubeModel.h"
#include "PlayingState.h"
#include "TestState.h"
#include "RegisterScoreState.h"
#include "ScoreViewerState.h"
#include "Timer.h"
#include "MouseTestState.h"
#include "MenuState.h"
#include "InfoState.h"

GameLogic::GameLogic() {
	//ShapeObject playerObject(0, 0, 0, std::make_shared<CubeShape>(CubeShape(1)));
	/*player = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, std::make_shared<CubeShape>(CubeShape(1)), 0.25));
	objects.push_back(std::shared_ptr<GameObject>(player));*/
    setState(State::MENU);
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

void GameLogic::setPerspective(bool setModelView) {
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

void GameLogic::handleSpecialInput(int key, int x, int y) {
    if (!states.empty()) {
        getCurrentState()->handleSpecialInput(key, x, y);
    }
}

void GameLogic::handleSpecialInputUp(int key, int x, int y) {
    if (!states.empty()) {
        getCurrentState()->handleSpecialInputUp(key, x, y);
    }
}

void GameLogic::mouseMotion(int x, int y)
{
    getCurrentState()->mouseMotion(x, y);
}

void GameLogic::mouse(int button, int state, int x, int y) {
    getCurrentState()->mouse(button, state, x, y);
}

void GameLogic::activeMouseMotion(int x, int y) {
    if (!states.empty())
        getCurrentState()->activeMouseMotion(x, y);
}

void GameLogic::resumeGame()
{
    pushState(State::PLAYING);
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
   case State::SCORE:
        states.emplace(new RegisterScoreState(this));
        break;
   case State::LEADERBOARD:
       states.emplace(new ScoreViewerState(this));
        break;
   /*case State::MOUSE:
       states.emplace(new MouseTestState(this));
       break;*/
   case State::MENU:
       states.emplace(new MenuState(this));
       break;
   case State::INFO:
       states.emplace(new InfoState(this));
       break;
   case State::PAUSE:
       states.emplace(new MenuState(this, true));
       break;
    default:
        states.emplace(new TestState(this));
        break;
    }
    getCurrentState()->playBackground();
    setPerspective();

}

void GameLogic::setAndPushState(State first, State tos) {
    //changes current state and also pushes a new on as TOS
    setState(first);
    pushState(tos);

}

void GameLogic::popState() {
    //getCurrentState()->dropBackground();
    delete(states.top());
    states.pop();
    if (!states.empty())
        getCurrentState()->playBackground();
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
