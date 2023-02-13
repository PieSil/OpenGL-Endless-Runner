#pragma once
#include<vector>
#include <stack>
#include<memory>
#include"GameObject.h"
#include"ShapeObject.h"
#include"Model.h"

class GameState; //definition needed to avoid circular inclusion

enum class State {
	//possible states
	PLAYING, TEST, SCORE, LEADERBOARD
};


//GameLogic class manages current game state and forwards functions calls (e.g. setCamera(), display(), to that specifica state)

class GameLogic {
public:
	GameLogic();

	void display();

	void update();

	void setCamera();

	void setPerspective(bool setModelView = true);

	void handleInput(unsigned char key, int x, int y);

	void handleInputUp(unsigned char key, int x, int y);

	void pushState(State state);

	void popState();

	void setState(State state);

	void pressKey(char key) {
		keyBuffer = key;
	}

	GameState* getCurrentState() const;

private:
	//std::vector<std::shared_ptr<GameObject>> objects;
	//std::shared_ptr<GameObject> player;
	std::stack<GameState*> states; //implements a stack structure for states, this allows to keep a state "progress" even when changing states
								   //e. g. the game is in the PLAYING state, the user presses the pause button, the PAUSE state gets pushed on top of the stack
								   //(and the underlying PLAYING state instance remains active)
								   //the user does something then closes the pause menu, the PAUSE state gets popped from the stack, and the user goes back to 
								   //the PLAYING state which has not "lost" any progress -> the user keeps playing
	char keyBuffer;
};