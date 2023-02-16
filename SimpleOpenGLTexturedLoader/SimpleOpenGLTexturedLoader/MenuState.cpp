#include "MenuState.h"
#include "Hitbox.h"
#include "Context.h"
float scaleMultFact = .5;
float scaleFactor =  0.0302175377;

void MenuState::display()
{

	//glPushMatrix();
	GameState::display();
	float xPos = Context::getContext()->getRelativeWindowX(1/2.f);
	float yPos = Context::getContext()->getRelativeWindowY(1/2.f);
	menu.setPosX(xPos);
	menu.setPosY(yPos);
	startButton.setPosX(xPos);
	startButton.setPosY(yPos);
	menu.display();
	startButton.display();
	//glPopMatrix();
}

void MenuState::handleInput(unsigned char key, int x, int y)
{
}

MenuState::MenuState(GameLogic* pointer, bool persp) : GameState(pointer, persp),
game(pointer), scaleSet(false)
{
	/*float scaleFactor = Context::getContext()->getScaleFactor();
	scaleFactor *= scaleMultFact;*/
	aiVector3D scale = (scaleFactor, scaleFactor, scaleFactor);
	menu = ShapeObject(0, 0, 0, ModelRepository::getModel(GAME_MENU), scale);
	startButton = ShapeObject(0, 0, 0, ModelRepository::getModel(START_BUTTON), scale);
}

void MenuState::mouseMotion(int x, int y)
{
}

void MenuState::mouse(int button, int state, int x, int y) {

	aiVector3D* v1 = new aiVector3D(0, 0, 0);
	aiVector3D* v2 = new aiVector3D(0, 0, 0);
	startButton.getHitbox(v1, v2); // hitbox of start button
	/*float scaleFactor = Context::getContext()->getScaleFactor();
	*v1 = *v1 / scaleFactor;
	*v2 = *v2 / scaleFactor;*/
	Hitbox h = Hitbox(*v1, *v2);

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (mouseBboxIntersection(x - Context::getContext()->getWidth() / 2,
			y - Context::getContext()->getHeight() / 2, h))
			game->setState(State::PLAYING);
		break;
	default:
		break;
	}

	delete(v1, v2);
}
