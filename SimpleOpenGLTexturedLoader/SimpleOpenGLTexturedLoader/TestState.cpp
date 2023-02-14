#include "TestState.h"
#include "SphereModel.h"
#include "Const.h"
#include "Context.h"

TestState::TestState(GameLogic* game) : GameState(game, false) {
	//player = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, std::make_shared<SphereModel>(SphereModel(1))));
	player = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, std::make_shared<AssimpModel>(AssimpModel(HEART_ID))));
	objects.push_back(std::shared_ptr<GameObject>(player));
}

void TestState::update() {
	player->move(100);
}

void TestState::handleInput(unsigned char key, int x, int y) {
	volatile double posZ;
	//manages inputs, should depend on active state
	switch (key) {
		/*case 'w': case 'W':
			player->incrZSpeed(1.);
			break;
		case 's': case 'S':
			player->incrZSpeed(-1.);
			break;*/
	case 'w': case 'W':
		player->incrZSpeed(1.);
		break;
	case 's': case 'S':
		player->incrZSpeed(-1.);
		break;
	case 'c': case 'C':
		game->setState(State::PLAYING);
		break;
	case ' ':
		posZ = player->getPosz();
	default:
		break;
	}
}

void TestState::handleInputUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': case 'W':
		player->incrZSpeed(-1.);
	break;
	case 's': case 'S':
		player->incrZSpeed(1.);
	break;
	default:
		break;
	}
}

void TestState::display() {
	double scaleFactor = Context::getContext()->getScaleFactor();
	glScalef(1/scaleFactor, 1/scaleFactor, 1/scaleFactor);
	GameState::display();
}

