#include "ScoreViewerState.h"
#include "FileManager.h"
#include "Context.h"
#include "Const.h"
#include "GLutils.h"

ScoreViewerState::ScoreViewerState(GameLogic* game) : GameState(game, false) {
	//FileManager::getInstance()->openFile(SCORE_DIR, SCORE_FILENAME);
	scores = FileManager::getInstance()->readScores(SCORE_DIR, SCORE_FILENAME);
	//FileManager::getInstance()->closeFile();
}

void ScoreViewerState::handleInput(unsigned char key, int x, int y) {
	switch (key) {
	case 13: //enter
		game->setState(State::PLAYING);
			break;
		default:
			break;
	}
}

void ScoreViewerState::display() {
	glDisable(GL_LIGHTING);
	glColor3f(1, .5, 0);
	std::string out;

	//show leaderbord headline
	out = "TOP 5 SCORES: ";
	int textWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)out.c_str());
	float posX = (textWidth / (2.f * Context::getContext()->getWidth()) + textWidth / 2.f);
	float posY = (FONT_HEIGHT / (2.f * Context::getContext()->getHeight()) + (Context::getContext()->getHeight() / 2.f) - (FONT_HEIGHT + 10));

	//show leaderboard
	output(posX, posY,out);
	int i;
	for (i = 0; i < 5; i++) {
		try {
			out = scores.at(i).first + ": " + std::to_string(scores.at(i).second);
		}
		catch (const std::out_of_range& e) {
			out = "---: ---";
		}
		textWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)out.c_str());
		posX = (textWidth / (2.f * Context::getContext()->getWidth()) + textWidth / 2.f);
		posY = (FONT_HEIGHT / (2.f * Context::getContext()->getHeight()) + (Context::getContext()->getHeight() / 2.f) - (FONT_HEIGHT + 10 + 50*(1+i)));
		output(posX,posY,out);
	}

	//show score headline
	out = "YOUR SCORE: ";
	textWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)out.c_str());
	posX = (textWidth / (2.f * Context::getContext()->getWidth()) + textWidth / 2.f);
	posY -= (FONT_HEIGHT / (2.f * Context::getContext()->getHeight()) - FONT_HEIGHT+100);
	glColor3f(1, 1, 1);
	output(posX, posY, out);

	//show player score
	out = Context::getContext()->getPlayerName() + ": ";
	out += std::to_string(Context::getContext()->getScore());
	textWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)out.c_str());
	posX = (textWidth / (2.f * Context::getContext()->getWidth()) + textWidth / 2.f);
	posY -= (FONT_HEIGHT / (2.f * Context::getContext()->getHeight()) - 2*FONT_HEIGHT + 100);
	output(posX, posY, out.c_str());
	glEnable(GL_LIGHTING);
}
