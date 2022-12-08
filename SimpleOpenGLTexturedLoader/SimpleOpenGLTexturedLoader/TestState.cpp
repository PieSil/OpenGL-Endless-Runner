#include "TestState.h"
#include "SphereModel.h"

TestState::TestState(GameLogic* game) : GameState(game) {
	player = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, std::make_shared<SphereModel>(SphereModel(1)), 1));
	objects.push_back(std::shared_ptr<GameObject>(player));
}

void TestState::handleInput(unsigned char key) {
	//manages inputs, should depend on active state

	switch (key) {
	case 'w': case 'W':
		player->move(0, 0, 1.0);
		break;
	case 's': case 'S':
		player->move(0, 0, -1.0);
		break;
	case 'c': case 'C':
		game->setState(State::PLAYING);
		break;
	default:
		break;
	}
}
