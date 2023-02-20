#include "InfoState.h"
#include "AudioPlayer.h"
#include "Context.h"

InfoState::InfoState(GameLogic* game) : GameState(game, false, FAIRY_BACKGROUND) {
	ModelRepository::getModelRepository()->resetAllAnimations();
}

void InfoState::display() {
	//WARNING: ugliest code I've written my whole life

	GameState::drawBackground();
	glDisable(GL_DEPTH_TEST);
	aiVector3D* min = new aiVector3D(0, 0, 0);
	aiVector3D* max = new aiVector3D(0, 0, 0);
	glDisable(GL_LIGHTING);
	glColor3f(0, 0, 0);
	std::string out;
	float scaleFactor = Context::getContext()->getScaleFactor();

	//get a pointer to desired model and get its size
	std::shared_ptr<Model> model = ModelRepository::getModel(EMPTY_YELLOW);
	model->getHitbox(min, max);

	//display background textbox
	float scaleX = Context::getContext()->getScaleForTarget(900 *.8, max->x-min->x);
	float scaleY = Context::getContext()->getScaleForTarget(FONT_HEIGHT+20, max->y - min->y);
	float posX;
	float posY;
	float modelX;

	//print controls
	out = "Press [A] or [<-] to move left. Press [D]/or [->] to move right.";
	float textWidth;
	float leftX = Context::getContext()->getRelativeWindowX(1 / 10.f); //align text to the left
	posX = leftX;
	posY = Context::getContext()->getRelativeWindowY(1 / 10.f);
	modelX = leftX - 300;
	glEnable(GL_LIGHTING);
	model->display(modelX, posY-3+FONT_HEIGHT/2.f, 0, aiVector3D(scaleX, scaleY, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	out = "Press [SPACEBAR] to jump.";
	posY = Context::getContext()->getRelativeWindowY(2 / 10.f);
	glEnable(GL_LIGHTING);
	model->display(modelX, posY - 3 + FONT_HEIGHT / 2.f, 0, aiVector3D(scaleX, scaleY, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	//print rupees rules
	out = "Collecting: ";
	posY = Context::getContext()->getRelativeWindowY(3 / 10.f);
	glEnable(GL_LIGHTING);
	model->display(modelX, posY - 3 + FONT_HEIGHT / 2.f, 0, aiVector3D(scaleX, scaleY, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	ShapeObject object = ShapeObject(posX, posY+FONT_HEIGHT/3.f, 0, ModelRepository::getModel(RUPEE_GREEN_ID), aiVector3D(scaleFactor, scaleFactor, scaleFactor));
	object.getHitbox(min, max);

	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = leftX - textWidth - (max->x - min->x) / 2.f;
	object.setPosX(posX);

	glEnable(GL_LIGHTING);
	object.display();
	glDisable(GL_LIGHTING);

	posX -= (max->x - min->x);
	out = "will earn you points.";
	output(posX, posY, out);

	//print sword controls
	posX = leftX;
	out = "Collecting: ";
	posY = Context::getContext()->getRelativeWindowY(4 / 10.f);
	glEnable(GL_LIGHTING);
	model->display(modelX, posY - 3 + FONT_HEIGHT / 2.f, 0, aiVector3D(scaleX, scaleY, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	object = ShapeObject(posX, posY, 0, ModelRepository::getModel(SWORD_POWERUP_ID), aiVector3D(scaleFactor, scaleFactor, scaleFactor));
	object.getHitbox(min, max);

	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = leftX - textWidth - (max->x - min->x) / 2.f;
	object.setPosX(posX);

	glEnable(GL_LIGHTING);
	object.display();
	glDisable(GL_LIGHTING);

	posX -= (max->x - min->x);
	out = "will let you shoot with [E] or [ENTER] for a short while.";
	output(posX, posY, out);

	//print advanced jump powerup
	out = "Collecting: ";
	posX = leftX;
	posY = Context::getContext()->getRelativeWindowY(5 / 10.f);
	glEnable(GL_LIGHTING);
	model->display(modelX, posY - 3 + FONT_HEIGHT / 2.f, 0, aiVector3D(scaleX, scaleY, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	object = ShapeObject(posX, posY+FONT_HEIGHT/2, 0, ModelRepository::getModel(ZELDALOGO_ID), aiVector3D(scaleFactor, scaleFactor, scaleFactor));
	object.getHitbox(min, max);

	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = leftX - textWidth - (max->x - min->x) / 2.f;
	object.setPosX(posX);

	glEnable(GL_LIGHTING);
	object.display();
	glDisable(GL_LIGHTING);

	posX -= (max->x - min->x);
	out = "will let you move during jumps for a short while.";
	output(posX, posY, out);

	//print heart powerup
	out = "Collecting: ";
	posX = leftX;
	posY = Context::getContext()->getRelativeWindowY(6 / 10.f);
	glEnable(GL_LIGHTING);
	model->display(modelX, posY - 3 + FONT_HEIGHT / 2.f, 0, aiVector3D(scaleX, scaleY, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	object = ShapeObject(posX, posY + FONT_HEIGHT / 2, 0, ModelRepository::getModel(HEART_ID), aiVector3D(scaleFactor, scaleFactor, scaleFactor));
	object.getHitbox(min, max);

	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = leftX - textWidth - (max->x - min->x) / 2.f;
	object.setPosX(posX);

	glEnable(GL_LIGHTING);
	object.display();
	glDisable(GL_LIGHTING);

	posX -= (max->x - min->x);
	out = "will let you recover 1 life (up to 3 lives).";
	output(posX, posY, out);

	//print obstacles rules
	out = "Avoid: ";
	posX = leftX;
	posY = Context::getContext()->getRelativeWindowY(7 / 10.f);
	glEnable(GL_LIGHTING);
	model->display(modelX, posY - 3 + FONT_HEIGHT / 2.f, 0, aiVector3D(scaleX, scaleY, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	object = ShapeObject(posX, posY + FONT_HEIGHT/3.f, 0, ModelRepository::getModel(CROSS_ID), aiVector3D(scaleFactor, scaleFactor, scaleFactor));
	object.getHitbox(min, max);

	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = leftX - textWidth - (max->x - min->x) / 2.f;
	object.setPosX(posX);

	glEnable(GL_LIGHTING);
	object.display();
	glDisable(GL_LIGHTING);

	posX -= (max->x - min->x);
	out = "or shoot them to earn points.";
	output(posX, posY, out);

	out = "Press [BACKSPACE] anytime to pause the game.";
	posX = leftX;
	posY = Context::getContext()->getRelativeWindowY(8 / 10.f);
	glEnable(GL_LIGHTING);
	model->display(modelX, posY - 3 + FONT_HEIGHT / 2.f, 0, aiVector3D(scaleX, scaleY, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);

	out = "Press [ENTER] when you are ready to start.";
	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
	posY = Context::getContext()->getRelativeWindowY(9 / 10.f);
	modelX = Context::getContext()->getRelativeWindowX(.5);
	model->getHitbox(min, max);
	scaleX = Context::getContext()->getScaleForTarget(textWidth+100, max->x - min->x);
	glEnable(GL_LIGHTING);
	model->display(modelX, posY - 3 + FONT_HEIGHT / 2.f, 0, aiVector3D(scaleX, scaleY, 1));
	glDisable(GL_LIGHTING);
	output(posX, posY, out);



	////show leaderbord headline
	//out = TOP5_STRING;
	//float textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());

	//float posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
	//float posY = Context::getContext()->getRelativeWindowY(1 / 10.f);

	////get x and y scale factors based on text size
	//float xScale = Context::getContext()->getScaleForTarget(textWidth + 30, max->x - min->x);
	//float yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);

	////show leaderboard
	//glEnable(GL_LIGHTING);
	//backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	//glDisable(GL_LIGHTING);
	//output(posX, posY, out);
	//int i;
	//for (i = 0; i < 5; i++) {
	//	try {
	//		out = scores.at(i).first + ": " + std::to_string(scores.at(i).second);
	//	}
	//	catch (const std::out_of_range& e) {
	//		out = DEFAULT_STRING;
	//	}
	//	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	//	posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
	//	posY = Context::getContext()->getRelativeWindowY((2 + i) / 10.f);
	//	//get x and y scale factors based on text size
	//	xScale = Context::getContext()->getScaleForTarget(textWidth + 30, max->x - min->x);
	//	yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);

	//	glEnable(GL_LIGHTING);
	//	backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	//	glDisable(GL_LIGHTING);
	//	output(posX, posY, out);
	//}


	//if (Context::getContext()->getPlayerName().size() != 0) {
	//	backgroundModel = (ModelRepository::getModel(EMPTY_YELLOW));
	//	backgroundModel->getHitbox(min, max);

	//	//show score headline
	//	out = YOUR_SCORE_STRING;
	//	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	//	posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
	//	posY = Context::getContext()->getRelativeWindowY(8 / 10.f);
	//	xScale = Context::getContext()->getScaleForTarget(textWidth + 30, max->x - min->x);
	//	yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);
	//	glColor3f(0, 0, 0);

	//	//show player score
	//	glEnable(GL_LIGHTING);
	//	backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	//	glDisable(GL_LIGHTING);
	//	output(posX, posY, out);

	//	//print player score
	//	out = Context::getContext()->getPlayerName() + ": ";
	//	out += std::to_string(Context::getContext()->getScore());
	//	textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	//	posX = Context::getContext()->getRelativeWindowX(.5, -textWidth * .5);
	//	posY = Context::getContext()->getRelativeWindowY(9 / 10.f);
	//	xScale = Context::getContext()->getScaleForTarget(textWidth + 30, max->x - min->x);
	//	yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);
	//	output(posX, posY, out.c_str());

	//	glEnable(GL_LIGHTING);
	//	backgroundModel->display(posX - textWidth * .5, posY + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	//	glDisable(GL_LIGHTING);
	//	output(posX, posY, out);
	//}

	glEnable(GL_LIGHTING);
	GameState::display();
	delete (min, max);
	glEnable(GL_DEPTH_TEST);

}

void InfoState::handleInput(unsigned char key, int x, int y) {
	switch (key) {
	case 13: //enter
		AudioPlayer::playSound(CLICK_SOUND);
		game->setState(State::PLAYING);
	}

}

void InfoState::update(){
	GameState::update();
	ModelRepository::getModelRepository()->animateModels();
}
