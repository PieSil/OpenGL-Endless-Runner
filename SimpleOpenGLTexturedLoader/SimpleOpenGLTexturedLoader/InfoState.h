#pragma once
#include "GameState.h"
class InfoState : public GameState {
public:
	InfoState(GameLogic* game);
	void display() override;
	void handleInput(unsigned char key, int x, int y) override;
	void update() override;

private:

};

