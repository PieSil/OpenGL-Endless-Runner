#include "MenuState.h"
#include "Hitbox.h"
#include "Context.h"
#include "AudioPlayer.h"

float scaleMultFact = .5;
float scaleFactor =  0.0302175377;

void MenuState::display()
{
	glDisable(GL_DEPTH_TEST);
	aiVector3D* min = new aiVector3D(0, 0, 0);
	aiVector3D* max = new aiVector3D(0, 0, 0);

	menu.getHitbox(min, max, true);

	//glPushMatrix();
	GameState::display();
	float xPos = Context::getContext()->getRelativeWindowX(1/2.f);
	float yPos = Context::getContext()->getRelativeWindowY(1/2.f);
	//float xScale = Context::getContext()->getOrthoScaleX();
	//float yScale = Context::getContext()->getOrthoScaleY();
	float windowWidth = Context::getContext()->getWidth();
	float windowHeight = Context::getContext()->getHeight();
	float menuWidth = max->x - min->x;
	float menuHeight = max->y - min->y;
	float xScale = 1;
	float yScale = 1;
	if(menuWidth != windowWidth)
		xScale = Context::getContext()->getScaleForTarget(windowWidth, menuWidth);
	if(menuHeight != windowHeight)
		yScale = Context::getContext()->getScaleForTarget(windowHeight, menuHeight);
	menu.adjustScale(aiVector3D(xScale/1.15, yScale, 1));
	startButton.adjustScale(aiVector3D(xScale, yScale, 1));
	//menu.setScale(aiVector3D(xScale, yScale, 1));
	//startButton.setScale(aiVector3D(xScale, yScale, 1));
	menu.setPosX(xPos);
	menu.setPosY(yPos);
	startButton.setPosX(xPos);
	startButton.setPosY(yPos);
	menu.display();
	startButton.display();
	//glPopMatrix();

	delete(min, max);
	glEnable(GL_DEPTH_TEST);
}

void MenuState::handleInput(unsigned char key, int x, int y)
{
}

MenuState::MenuState(GameLogic* pointer, bool persp) : GameState(pointer, persp),
game(pointer), scaleSet(false)
{
	//float scaleFactor = Context::getContext()->getScaleFactor();
	//scaleFactor *= scaleMultFact;
	aiVector3D scale = aiVector3D(scaleFactor, scaleFactor, 1);
	//aiVector3D scale = (1, 1, 1);
	menu = ShapeObject(0, 0, 0, ModelRepository::getModel(GAME_MENU));
	startButton = ShapeObject(0, 0, 0, ModelRepository::getModel(START_BUTTON));
	if (AudioPlayer::setBackground(FAIRY_BACKGROUND)) {
		AudioPlayer::dropBackground();
		AudioPlayer::playBackground();
	}
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
