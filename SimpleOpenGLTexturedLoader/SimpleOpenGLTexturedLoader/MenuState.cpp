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

	//start by placing background in the middle of the scene
	float xPos = Context::getContext()->getRelativeWindowX(1/2.f);
	float yPos = Context::getContext()->getRelativeWindowY(1/2.f);
	
	//get window height and width
	float windowWidth = Context::getContext()->getWidth();
	float windowHeight = Context::getContext()->getHeight();

	//get menu (background model) width and height
	float menuWidth = max->x - min->x;
	float menuHeight = max->y - min->y;
	float xScale = 1;
	float yScale = 1;

	//determine a new scale factor if needed
	if (menuWidth != windowWidth || menuHeight != windowHeight) {
		xScale = Context::getContext()->getScaleForTarget(windowWidth, menuWidth);
		yScale = Context::getContext()->getScaleForTarget(windowHeight, menuHeight);
	}

	//adjust scale
	menu.adjustScale(aiVector3D(xScale/1.15, yScale, 1));
	startButton.adjustScale(aiVector3D(xScale, yScale, 1));
	leaderboardButton.adjustScale(aiVector3D(xScale, yScale, 1));
	escButton.adjustScale(aiVector3D(xScale, yScale, 1));

	//position and display background and buttons
	menu.setPosX(xPos);
	menu.setPosY(yPos);

	//update button y position in order to place it at 2/5 of the window height
	yPos = Context::getContext()->getRelativeWindowY(1 / 4.f);
	startButton.setPosX(xPos);
	startButton.setPosY(yPos);

	//update button y position in order to place it at 3/5 of the window height
	yPos = Context::getContext()->getRelativeWindowY(2 / 4.f);
	leaderboardButton.setPosX(xPos);
	leaderboardButton.setPosY(yPos);

	//update button y position in order to place it at 1/3 of the window height
	yPos = Context::getContext()->getRelativeWindowY(3 / 4.f);
	escButton.setPosX(xPos);
	escButton.setPosY(yPos);


	//display buttons and background
	menu.display();
	startButton.display();
	leaderboardButton.display();
	escButton.display();
	//glPopMatrix();

	delete(min, max);
	glEnable(GL_DEPTH_TEST);
}

void MenuState::handleInput(unsigned char key, int x, int y)
{
}

MenuState::MenuState(GameLogic* pointer, bool pause, bool persp) : GameState(pointer, persp, FAIRY_BACKGROUND),
game(pointer), pause(pause)
{
	aiVector3D scale = aiVector3D(scaleFactor, scaleFactor, 1);
	//aiVector3D scale = (1, 1, 1);
	menu = ShapeObject(0, 0, 0, ModelRepository::getModel(GAME_MENU));
	if (!pause) {
		startButton = ShapeObject(0, 0, 0, ModelRepository::getModel(START_BUTTON));
	}
	else {
		startButton = ShapeObject(0, 0, 0, ModelRepository::getModel(RESUME_BUTTON));
	}
	escButton = ShapeObject(0, 0, 0, ModelRepository::getModel(EXIT_BUTTON));
	leaderboardButton = ShapeObject(0, 0, 0, ModelRepository::getModel(STATS_BUTTON));
}

void MenuState::mouseMotion(int x, int y)
{
}

void MenuState::mouse(int button, int state, int x, int y) {

	aiVector3D* v1 = new aiVector3D(0, 0, 0);
	aiVector3D* v2 = new aiVector3D(0, 0, 0);

	// build hitbox of start button
	startButton.getHitbox(v1, v2);
	Hitbox startHitbox = Hitbox(*v1, *v2);

	// build hitbox of stats button
	leaderboardButton.getHitbox(v1, v2);
	Hitbox leadHitbox = Hitbox(*v1, *v2);

	//build hitbox of exit button
	escButton.getHitbox(v1, v2);
	Hitbox escHitbox = Hitbox(*v1, *v2);

	float mouseX = x -Context::getContext()->getWidth() / 2.f;	//adjust mouse X by an offset
	float mouseY = - y + Context::getContext()->getHeight()/2.f;	//adjust mouse Y by an offset

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (mouseBboxIntersection(mouseX,mouseY, startHitbox)) {
			AudioPlayer::playSound(CLICK_SOUND);
			if (pause) {
				game->popState(); //unpause
			}
			else {
				game->setState(State::INFO);
			}
		}
		else if (mouseBboxIntersection(mouseX, mouseY, leadHitbox)) {
			AudioPlayer::playSound(CLICK_SOUND);
			game->pushState(State::LEADERBOARD);
		}
		else if (mouseBboxIntersection(mouseX, mouseY, escHitbox)) {
			AudioPlayer::playSound(CLICK_SOUND);
			exit(1);
		}
		break;
	default:
		break;
	}

	delete(v1, v2);
}
