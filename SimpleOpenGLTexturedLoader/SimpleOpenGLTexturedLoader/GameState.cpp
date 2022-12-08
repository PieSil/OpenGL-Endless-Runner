#include "GameState.h"

GameState::GameState(GameLogic* game) : game(game) {
	//this->game = std::shared_ptr<GameLogic>(game);
	setCamera();
}

void GameState::display() {
	//call display function of every object in the scene
	for (auto obj = objects.begin(); obj != objects.end(); obj++) {
		(*obj)->display();
	}
	//setCamera(); //sets the camera AFTER rendering the scene
}

void GameState::update() {
	//call update function of every object in the scene
	//object's update function defines a behaviour that needs to be applied at every frame (e.g. animations)
	for (auto obj = objects.begin(); obj != objects.end(); obj++) {
		(*obj)->update();
	}
}

void GameState::setCamera() {
	glLoadIdentity();
	//glTranslatef(0, 0, -20);
	//glRotatef(30, 1., 0., 0.);
	gluLookAt(0, 5.7735, -10, 0, 0, 0, 0, 1, 0);
	//gluLookAt()
}

void GameState::addGameObject(float x, float y, float z, std::shared_ptr<Model> shape) {
	objects.push_back(std::make_shared<ShapeObject>(ShapeObject(x, y, z, shape)));
}
