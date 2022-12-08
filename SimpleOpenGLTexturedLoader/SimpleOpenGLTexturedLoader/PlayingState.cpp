//
// Created by Pietro on 2019-07-12.
//
#include "GameState.h"
#include "GameLogic.h"
#include "PlayingState.h"
#include "CubeModel.h"
#include "FairyModel.h"

PlayingState::PlayingState(GameLogic* game) : GameState(game) {
	//player = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, std::make_shared<CubeModel>(CubeModel(1)), 0.25));
	player = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, std::make_shared<FairyModel>(FairyModel()), .25));
	objects.push_back(std::shared_ptr<GameObject>(player));
}

void PlayingState::handleInput(unsigned char key) {
	//manages inputs, should depend on active state
	switch (key) {
	case 'w': case 'W':
		player->move(0, 0, 1.0);
		break;
	case 's': case 'S':
		player->move(0, 0, -1.0);
		break;
	case 'c': case 'C':
		game->setState(State::TEST);
		break;
	default:
		break;
	}
}