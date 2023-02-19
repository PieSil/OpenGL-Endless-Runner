#include "RegisterScoreState.h"
#include "Const.h"
#include "Context.h"
#include "GLutils.h"
#include "AudioPlayer.h"

RegisterScoreState::RegisterScoreState(GameLogic* game) : GameState(game, false) {
	Context::getContext()->clearPlayerName();
	charLimit = 20;
	if (AudioPlayer::setBackground(FAIRY_BACKGROUND)) {
		AudioPlayer::dropBackground();
		AudioPlayer::playBackground();
	}
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
		break; //ignore spaces
	default:
		if (Context::getContext()->getPlayerName().size() < charLimit)
			Context::getContext()->concatCharToPlayerName(key);
		break;
	}
}

void RegisterScoreState::display()
{
	//set up display mode (disable materials, disable depth test)
	GameState::drawBackground();
	setCamera();
	aiVector3D* min = new aiVector3D(0, 0, 0);
	aiVector3D* max = new aiVector3D(0, 0, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	std::shared_ptr<Model> backgroundModel = ModelRepository::getModel(EMPTY_GREEN);
	backgroundModel->getHitbox(min, max);

	glColor3f(.8, 0, 0); //use dark red for text
	//print player score
	std::string out = "SCORE: " + std::to_string(Context::getContext()->getScore());
	float textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	float posX = Context::getContext()->getRelativeWindowX(.5, -textWidth / 2.f);
	float posY = Context::getContext()->getRelativeWindowY(1 / 5.f, -FONT_HEIGHT / 2.f);

	//get x and y scale factors based on text size
	float xScale = Context::getContext()->getScaleForTarget(textWidth + 100, max->x - min->x);
	float yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 50, max->y - min->y);
	glEnable(GL_LIGHTING);
	backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out.c_str());

	//print message
	out = "Insert your name, press [ENTER] to confirm";
	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());

	posX = Context::getContext()->getRelativeWindowX(.5, -textWidth/2.f);
	posY = Context::getContext()->getRelativeWindowY( 2 / 5.f, -FONT_HEIGHT/2.f);

	xScale = Context::getContext()->getScaleForTarget(textWidth + 100, max->x - min->x);
	yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 50, max->y - min->y);
	glEnable(GL_LIGHTING);
	backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	//dynamically print player name
	glColor3f(0, 0, 0); //use black for text
	backgroundModel = ModelRepository::getModel(EMPTY_YELLOW);
	backgroundModel->getHitbox(min, max);
	out = Context::getContext()->getPlayerName();
	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = Context::getContext()->getRelativeWindowX(.5, -textWidth / 2.f);
	posY = Context::getContext()->getRelativeWindowY(3/5.f, -FONT_HEIGHT / 2.f);
	//float textBoxTargetWidth = Context::getContext()->getWidth() * .5; //make text box large as 50% of window
	//xScale = Context::getContext()->getScaleForTarget(textBoxTargetWidth, max->x - min->x);
	//yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 50, max->y - min->y);

	glEnable(GL_LIGHTING);
	backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, Context::getContext()->getPlayerName());
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	delete(min, max);
}
