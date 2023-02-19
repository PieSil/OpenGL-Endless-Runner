#pragma once
#include "GameState.h"
#include "FileManager.h"
#include <string>

class RegisterScoreState : public GameState {
public:
	explicit RegisterScoreState(GameLogic* game);
	void handleInput(unsigned char key, int x, int y) override;
	void handleInputUp(unsigned char key, int x, int y) override {};
	void display() override;
private:
	int charLimit = 20;
};

