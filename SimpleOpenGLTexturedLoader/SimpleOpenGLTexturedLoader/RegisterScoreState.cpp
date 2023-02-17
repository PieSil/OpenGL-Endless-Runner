#include "RegisterScoreState.h"
#include "Const.h"
#include "Context.h"
#include "GLutils.h"

RegisterScoreState::RegisterScoreState(GameLogic* game) : GameState(game, false) {
	Context::getContext()->clearPlayerName();
}

void RegisterScoreState::handleInput(unsigned char key, int x, int y){
	switch (key) {
	case 8: // backspace
	case 127: // delete
		Context::getContext()->deletePlayerNameChar();
		break;
	case 13: //enter
		//FileManager::getInstance()->openFile(SCORE_DIR, SCORE_FILENAME);
		if (!Context::getContext()->getPlayerName().empty()) {
			FileManager::getInstance()->writeScore(Context::getContext()->getPlayerName(), Context::getContext()->getScore(), SCORE_DIR, SCORE_FILENAME);
			//FileManager::getInstance()->closeFile();
			game->setState(State::LEADERBOARD); //replace with game over state
		}
		break;
	case 32: //spacebar
		key = ' ';
	default:
		Context::getContext()->concatCharToPlayerName(key);
		break;
	}
}

void RegisterScoreState::display()
{
	//set up display mode (disable materials, disable depth test)
	setCamera();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1); //use white for text

	//print player score
	std::string out = "SCORE: " + std::to_string(Context::getContext()->getScore());
	float textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	float posX = Context::getContext()->getRelativeWindowX(.5, -textWidth / 2.f);
	float posY = Context::getContext()->getRelativeWindowY(1 / 5.f, -FONT_HEIGHT / 2.f);
	output(posX, posY, out.c_str());

	//print message
	out = "Insert your name, press [ENTER] to confirm";
	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = Context::getContext()->getRelativeWindowX(.5, -textWidth/2.f);
	posY = Context::getContext()->getRelativeWindowY( 2 / 5.f, -FONT_HEIGHT/2.f);
	output(posX, posY, out);

	//dynamically proìint player name
	out = Context::getContext()->getPlayerName();
	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = Context::getContext()->getRelativeWindowX(.5, -textWidth / 2.f);
	posY = Context::getContext()->getRelativeWindowY(.5, -FONT_HEIGHT / 2.f);
	output(posX, posY, Context::getContext()->getPlayerName());
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}
