#include "RegisterScoreState.h"
#include "Const.h"
#include "Context.h"
#include "GLutils.h"

RegisterScoreState::RegisterScoreState(GameLogic* game) : GameState(game, true) {
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
		FileManager::getInstance()->writeScore(Context::getContext()->getPlayerName(), Context::getContext()->getScore(), SCORE_DIR, SCORE_FILENAME);
		//FileManager::getInstance()->closeFile();
		game->setState(State::LEADERBOARD); //replace with game over state
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
	output(0, 0, "Insert your name, press [ENTER] to confirm");
	output(0, -1, Context::getContext()->getPlayerName());
}
