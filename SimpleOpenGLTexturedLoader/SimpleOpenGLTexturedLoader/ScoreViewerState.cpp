#include "ScoreViewerState.h"
#include "FileManager.h"
#include "Context.h"
#include "Const.h"
#include "GLutils.h"
#include "Hitbox.h"
#include "AudioPlayer.h"
ScoreViewerState::ScoreViewerState(GameLogic* game) : GameState(game, false, FAIRY_BACKGROUND) {

	//reads scores from file
	scores = FileManager::getInstance()->readScores(SCORE_DIR, SCORE_FILENAME);

}

void ScoreViewerState::handleInput(unsigned char key, int x, int y) {
	switch (key) {
	case 13: //enter
		Context::getContext()->clearPlayerName();
		AudioPlayer::playSound(CLICK_SOUND);
		game->setState(State::MENU);
			break;
		default:
			break;
	}
}

void ScoreViewerState::display() {
	GameState::drawBackground();
	glDisable(GL_DEPTH_TEST);
	aiVector3D* min = new aiVector3D(0, 0, 0);
	aiVector3D* max = new aiVector3D(0, 0, 0);
	glDisable(GL_LIGHTING);
	glColor3f(.8, 0, 0);
	std::string out;

	//get a pointer to desired model and get its size
	std::shared_ptr<Model> backgroundModel = ModelRepository::getModel(EMPTY_GREEN);
	backgroundModel->getHitbox(min, max);

	//show leaderbord headline
	out = TOP5_STRING;
	float textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());

	float posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
	float posY = Context::getContext()->getRelativeWindowY(1 / 10.f);

	//get x and y scale factors based on text size
	float xScale = Context::getContext()->getScaleForTarget(textWidth + 30, max->x - min->x);
	float yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);

	//show leaderboard
	glEnable(GL_LIGHTING);
	backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);
	int i;
	for (i = 0; i < 5; i++) {
		try {
			out = scores.at(i).first + ": " + std::to_string(scores.at(i).second);
		}
		catch (const std::out_of_range& e) {
			out = DEFAULT_STRING;
		}
		textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
		posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
		posY = Context::getContext()->getRelativeWindowY((2 + i) / 10.f);
		//get x and y scale factors based on text size
		xScale = Context::getContext()->getScaleForTarget(textWidth + 30, max->x - min->x);
		yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);

		glEnable(GL_LIGHTING);
		backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
		glDisable(GL_LIGHTING);
		output(posX, posY, out);
	}

	backgroundModel = (ModelRepository::getModel(EMPTY_YELLOW));
	backgroundModel->getHitbox(min, max);
	glColor3f(0, 0, 0);
	if (Context::getContext()->getPlayerName().size() != 0) {

		//show score headline
		out = YOUR_SCORE_STRING;
		textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
		posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
		posY = Context::getContext()->getRelativeWindowY(7 / 10.f);
		xScale = Context::getContext()->getScaleForTarget(textWidth + 30, max->x - min->x);
		yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);
		

		//show player score
		glEnable(GL_LIGHTING);
		backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
		glDisable(GL_LIGHTING);
		output(posX, posY, out);

		//print player score
		out = Context::getContext()->getPlayerName() + ": ";
		out += std::to_string(Context::getContext()->getScore());
		textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
		posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
		posY = Context::getContext()->getRelativeWindowY(8 / 10.f);
		xScale = Context::getContext()->getScaleForTarget(textWidth + 30, max->x - min->x);
		yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);
		output(posX, posY, out.c_str());

		glEnable(GL_LIGHTING);
		backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
		glDisable(GL_LIGHTING);
		output(posX, posY, out);
	}

	out = "Press [ENTER] to get back to menu";
	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
	posY = Context::getContext()->getRelativeWindowY(8 / 10.f);
	xScale = Context::getContext()->getScaleForTarget(textWidth + 100, max->x - min->x);
	yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);
	output(posX, posY, out.c_str());
	glEnable(GL_LIGHTING);
	backgroundModel->display(posX - textWidth * .5, posY - 3 + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	glEnable(GL_LIGHTING);
	GameState::display();
	delete (min, max);
	glEnable(GL_DEPTH_TEST);
}
