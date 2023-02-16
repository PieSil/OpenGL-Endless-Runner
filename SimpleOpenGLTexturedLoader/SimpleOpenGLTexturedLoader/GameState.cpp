#include "GameState.h"
#include "Context.h"

GameState::GameState(GameLogic* game, bool persp) : game(game), persp(persp) {
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

void GameState::setPerspective(bool setModelView) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (persp) {
		gluPerspective(Context::getContext()->getFieldOfView(), Context::getContext()->getAspectRatio(),
			1, 1000.0);  // Znear and Zfar 
	}
	else {
		glOrtho(-Context::getContext()->getWidth() / 2.f, Context::getContext()->getWidth() / 2.f, -Context::getContext()->getHeight() / 2.f, Context::getContext()->getHeight() / 2.f, 0, 1000);
		//gluOrtho2D(-Context::getContext()->getWidth() / 2.f, Context::getContext()->getWidth() / 2.f, -Context::getContext()->getHeight() / 2.f, Context::getContext()->getHeight() / 2.f);
	}

	if(setModelView)
		glMatrixMode(GL_MODELVIEW);
}

void GameState::setCamera() {
	if (persp) {
		//glTranslatef(0, 0, -20);
		//glRotatef(30, 1., 0., 0.);
		glLoadIdentity();
		gluLookAt(0, 15, -20, 0, 0, 0, 0, 1, 0);
		//gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);
		//glLoadIdentity();
		//gluLookAt()
	}
	else {
		glLoadIdentity();
		gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);
	}
}
