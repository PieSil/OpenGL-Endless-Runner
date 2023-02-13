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
	std::string out;
	glClear(GL_COLOR_BUFFER_BIT);
	out = "TOP 5 SCORES: ";
	int w = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)out.c_str());
	float posX = w / (2.f * glutGet(GLUT_WINDOW_WIDTH));
	float posY = FONT_HEIGHT / (2.f * glutGet(GLUT_WINDOW_HEIGHT));

	
	output(w/2.f, 6*42, "TOP 5 SCORES: ");
	int i;
	for (i = 0; i < 5; i++) {
		try {
			out = scores.at(i).first + ": " + std::to_string(scores.at(i).second);
		}
		catch (const std::out_of_range& e) {
			out = "---: ---";
		}
		float posX = w / (.2 * glutGet(GLUT_WINDOW_WIDTH));
		float posY = FONT_HEIGHT / (.04 + ((float)i/10.f) * glutGet(GLUT_WINDOW_HEIGHT));
		output(w/2.f,(- (float)FONT_HEIGHT / 2.f - i * 42)+5*42, out);
	}

	output(w/2.f, ((float)FONT_HEIGHT / 2.f - (i + 4) * 42) + 6 * 42, "YOUR SCORE: ");
	out = Context::getContext()->getPlayerName() + ": ";
	out += std::to_string(Context::getContext()->getScore());
	output(w/2.f, ((float)FONT_HEIGHT / 2.f - (i + 5) * 42)+6*42, out.c_str());
}
