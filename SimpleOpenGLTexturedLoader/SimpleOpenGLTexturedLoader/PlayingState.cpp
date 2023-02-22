//
// Created by Pietro on 2019-07-12.
//
#include "GameState.h"
#include "GameLogic.h"
#include "PlayingState.h"
#include "CubeModel.h"
#include "FairyModel.h"
#include "AssimpModel.h"
#include "assimp.h"
#include "aiPostProcess.h"
#include "aiScene.h"
#include "Const.h"
#include "Context.h"
#include "Const.h"
#include "Hitbox.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#define COLL_DESPAWN_Z -12
#define PROJ_DESPAWN_Z COL_SPAWN_Z

PlayingState::PlayingState(GameLogic* game) : GameState(game, true, SUBWAY_BACK) {

	ModelRepository::getModelRepository()->resetAllAnimations();
	pointsToNextAccel = 20;
	aKeyPressed = false;
	dKeyPressed = false;
	leftArrowPressed = false;
	rightArrowPressed = false;
	mouseLastY = 0;
	lastYvalid = false;

	//reset game score
	Context::getContext()->resetScore();

	//set game speed
	Context::getContext()->setGameSpeed(10);
	collectibleSpawner = CollectibleSpawner();

	//create player object and add it to renderable objects
	player = std::make_shared<PlayerObject>(PlayerObject(0, 0, -5, ModelRepository::getModel(FAIRY_ID), aiVector3D(1,1,1), 10));
	objects.push_back(std::shared_ptr<GameObject>(player));

	UIText.push_back("LIVES: ");

	for (auto coll : collectibles) {
		coll->incrZSpeed(-1);
	}

	resetCameraAngle();
}

void PlayingState::display(){
	GameState::drawBackground(true);
	//call GameState display() function in order to render all elements in "object" list
	GameState::display();

	//then render all collectibles
	for (auto coll = collectibles.begin(); coll != collectibles.end(); coll++) {
		(*coll)->display();
	}

	for (auto proj = projectiles.begin(); proj != projectiles.end(); proj++) {
		(*proj)->display();
	}
	displayUI();
}

void PlayingState::update() {
	//play animations linked to models (e. g. rotation)
	ModelRepository::getModelRepository()->animateModels();

	if (player->isShooting() && player->shoot()) {
		spawnProjectile();
		AudioPlayer::playSound(SHOOT_SOUND);
	}

	if (pointsToNextAccel - Context::getContext()->getScore() <= 0) {
		pointsToNextAccel += 20;
		Context::getContext()->incrGameSpeed(2);
	}

	if (grounds.empty()) {
		//spawn ground, must be placed here because if placed in constructor may create some problems with Assimp
		spawnNewGround();
		spawnNewGround();
		//spawnNewGround();
	}
	else {
		//move ground
		bool groundErased = false;
		auto groundIterator = grounds.begin();
		while (!grounds.empty() && groundIterator != grounds.end()) {
			(*groundIterator).ground->move(Context::getContext()->getGameSpeed());
			(*groundIterator).lborder->move(Context::getContext()->getGameSpeed());
			(*groundIterator).rborder->move(Context::getContext()->getGameSpeed());
			(*groundIterator).linvisible->move(Context::getContext()->getGameSpeed());
			(*groundIterator).rinvisible->move(Context::getContext()->getGameSpeed());
			if ((*groundIterator).ground->getPosz() < -160) {
				deleteGround(*groundIterator);
				groundIterator = grounds.erase(groundIterator);
				groundErased = true;
			}
			else {
				groundIterator++;
			}
		}
		if (groundErased) {
			spawnNewGround();
		}
	}

	//update collectibles position
	auto collIterator = collectibles.begin();
	while (!collectibles.empty() && collIterator != collectibles.end()) {

		//move collectibles
		(*collIterator)->move(Context::getContext()->getGameSpeed());

		//check if collectible is too far back along Z, in that case destroy it
		if ((*collIterator)->getPosz() <= COLL_DESPAWN_Z) {
			collIterator = collectibles.erase(collIterator);

		}
		else {
			collIterator++;
		}
	}

	//update projectiles position
	auto projIterator = projectiles.begin();
	while (!projectiles.empty() && projIterator != projectiles.end()) {

		//move collectibles
		(*projIterator)->move();
		if ((*projIterator)->getPosz() >= PROJ_DESPAWN_Z) {
			projIterator = projectiles.erase(projIterator);

		}
		else {
			projIterator++;
		}

	}

	//spawn collectibles
	auto newCollectibles = collectibleSpawner.spawnCollectibles();

	if (!newCollectibles.empty()) {
		for (std::shared_ptr<CollectibleObject> coll : newCollectibles) {
			collectibles.push_back(coll);
		}
	}

	player->move();
	GameState::update();

	//check collisions
	checkCollisions();

	//check player status:
	if (player->getLives() <= 0) {
		resetCameraAngle();
		AudioPlayer::stopAllSounds();
		game->setState(State::SCORE); //register player score
	}
}

void PlayingState::handleInput(unsigned char key, int x, int y) {
	//manages inputs, should depend on active state

	switch (key) {
	/*case 'w': case 'W':
		player->incrZSpeed(1.);
		break;
	case 's': case 'S':
		player->incrZSpeed(-1.);
		break;*/
	case 8: // backspace

		//reset a series of parameters before pausing the game
		player->resetXSpeed();
		aKeyPressed = false;
		aKeyPressed = false;
		leftArrowPressed = false;
		rightArrowPressed = false;
		lastYvalid = false;
		player->setShooting(false);

		game->pushState(State::PAUSE);
		break;
	case 'a': case 'A':
		if ((!leftArrowPressed && !rightArrowPressed) && (player->isOnGround() || player->isFlightActive())) {
			aKeyPressed = true;
			player->incrXSpeed(1.);
			player->setInputRecorded(true);
		}
		break;
	case 'd': case 'D':
		if ((!leftArrowPressed && !rightArrowPressed) && (player->isOnGround() || player->isFlightActive())) {
			dKeyPressed = true;
			player->incrXSpeed(-1.);
			player->setInputRecorded(true);
		}
		break;
	case 'e': case 'E': case 13: //13 = enter:
		if (!player->isShooting()) {
			//spawn projectile
			player->setShooting(true);
		}
		break;
	case 32: //spacebar
		if (player->isOnGround()) {
			if (!player->isFlightActive()) {
				player->setInputRecorded(false);
				player->resetXSpeed();
			}
			player->setJumpSpeed(25);
			player->setOnGround(false);
		}
		break;
	/*
	case 'r': case 'R':
		player->move(0, 1, 0);
		break;
	case 'f': case 'F':
		player->move(0, -1, 0);
		break;
	*/
	default:
		break;
	}
}

void PlayingState::handleInputUp(unsigned char key, int x, int y) {
	switch (key) {
	//case 'w': case 'W':
	//	player->incrZSpeed(-1.);
	//	break;
	//case 's': case 'S':
	//	player->incrZSpeed(1.);
	//	break;
	case 'a': case 'A':
		if ((player->isOnGround() || player->isFlightActive()) && player->isInputRecorded()) {
			aKeyPressed = false;
			player->incrXSpeed(-1.);
			//player->setInputRecorded(false);
		}

		break;
	case 'd': case 'D': 
		if ((player->isOnGround() || player->isFlightActive()) && player->isInputRecorded()) {
			dKeyPressed = false;
			player->incrXSpeed(1.);
			//player->setInputRecorded(false);
		}
		break;
	case 'e': case 'E': case 13: //13 = enter:
		if (player->isShooting()) {
			player->setShooting(false);
		}
		break;
	default:
		break;
	}

	if (!aKeyPressed && !dKeyPressed && !leftArrowPressed && !rightArrowPressed) {
		player->setInputRecorded(false);
	}
}

void PlayingState::handleSpecialInput(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if ((!aKeyPressed && !dKeyPressed) && (player->isOnGround() || player->isFlightActive())) {
			leftArrowPressed = true;
			player->incrXSpeed(1.);
			player->setInputRecorded(true);
		}
		break;
	case GLUT_KEY_RIGHT:
		if ((!aKeyPressed && !dKeyPressed) && (player->isOnGround() || player->isFlightActive())) {
			rightArrowPressed = true;
			player->incrXSpeed(-1.);
			player->setInputRecorded(true);
		}
		break;
	default:
		break;
	}
}

void PlayingState::handleSpecialInputUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if ((player->isOnGround() || player->isFlightActive()) && player->isInputRecorded()) {
			leftArrowPressed = false;
			player->incrXSpeed(-1.);
			//player->setInputRecorded(false);
		}
		break;
	case GLUT_KEY_RIGHT:
		if ((player->isOnGround() || player->isFlightActive()) && player->isInputRecorded()) {
			rightArrowPressed = false;
			player->incrXSpeed(1.);
			//player->setInputRecorded(false);
		}
		break;
	default:
		break;
	}

	if (!aKeyPressed && !dKeyPressed && !leftArrowPressed && !rightArrowPressed) {
		player->setInputRecorded(false);
	}
}


void PlayingState::mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			mouseLastY = y;
			lastYvalid = true;
		}

		else if (state == GLUT_UP) {
			lastYvalid = false;
		}
		break;
	default:
		break;
	}

}

void PlayingState::activeMouseMotion(int x, int y) {

	if (lastYvalid) {
		if (y > mouseLastY) {
			incrCameraAngle(1);
		}
		else if (y < mouseLastY) {
			incrCameraAngle(-1);
		}

		mouseLastY = y;
	}
}

void PlayingState::checkCollisions() {
	//check all relevant collisions between objects in current level e. g. player and ground, player and collectible items

	aiVector3D* playerMin = new aiVector3D(0, 0, 0);
	aiVector3D* playerMax = new aiVector3D(0, 0, 0);
	player->getHitbox(playerMin, playerMax);
	int playerX = (int)player->getPosx();
	int playerY = (int)player->getPosy();
	int playerZ = (int)player->getPosz();

	Hitbox playerHitbox = Hitbox(*playerMin, *playerMax); //get player hitbox

	for (auto current : collidables) { //iterate over all collidable elements

		int currentX = (int)current->getPosx();
		int currentY = (int)current->getPosy();
		int currentZ = (int)current->getPosz();

		aiVector3D* currentMin = new aiVector3D(0, 0, 0);
		aiVector3D* currentMax = new aiVector3D(0, 0, 0);
		current->getHitbox(currentMin, currentMax);

		//build hitbox from min and max
		Hitbox collidableHitbox(*currentMin, *currentMax);

		if (bboxIntersection(playerHitbox, collidableHitbox)) {
			printf("Player colliding with an object\n");
			//Collision detected, manage collision

			//leave like this for now, elaborate collision resolution only if needed
			player->revertMovement(true, false, true);
		}

		delete currentMin;
		delete currentMax;
		//}
	}


	if (!player->isOnGround()) {  //if player is not onGround also check collision with ground
		for (auto currentGround : grounds) {
			aiVector3D* groundMin = new aiVector3D(0, 0, 0);
			aiVector3D* groundMax = new aiVector3D(0, 0, 0);
			currentGround.ground->getHitbox(groundMin, groundMax);
			Hitbox groundHitbox = Hitbox(*groundMin, *groundMax);

			if (bboxIntersection(playerHitbox, groundHitbox)) {
				player->revertMovement(false, true, false); //revert movement only on y axis
				player->setOnGround(true);
				player->setJumpSpeed(0);
			}
			delete groundMin;
			delete groundMax;
			if (player->isOnGround()) {
				break; //stop iterating if player is already on ground
			}
		}
	}

	auto collIterator = collectibles.begin();

	//iterate over all collectibles
	//some collectibles may be removed during this process, another loop structure is needed <-- I tried to use same loop structure as above, but it did not work
	while (!collectibles.empty() && collIterator != collectibles.end()) {

		bool collisionDetected = false;

		int currentX = (int)(*collIterator)->getPosx();
		int currentY = (int)(*collIterator)->getPosy();
		int currentZ = (int)(*collIterator)->getPosz();

		aiVector3D* collMin = new aiVector3D(0, 0, 0);
		aiVector3D* collMax = new aiVector3D(0, 0, 0);
		(*collIterator)->getHitbox(collMin, collMax);

		//build hitbox from min and max
		Hitbox collectibleHitbox(*collMin, *collMax);

		//only check hitboxes if objects are close enough
		if ((currentX >= playerX - 5 && currentX <= playerX + 5) && (currentY >= playerY - 5 && currentY <= playerY + 5) && (currentZ >= playerZ - 5 && currentZ <= playerZ + 5)) {

			if (bboxIntersection(playerHitbox, collectibleHitbox))  {
				//if a collision is detected apply the collectible effect to player, then erase the collectible
				//collIterator MUST NOT be updated during this iteration
				printf("Player collided with collectible\n");
				if ((*collIterator)->applyEffect(player.get())) {
					collIterator = collectibles.erase(collIterator);
					collisionDetected = true;
				}
			}
		} 

		//if current collectible is a spike check collisions with projectiles
		if (!collisionDetected && (*collIterator)->getCollType() == CollectibleBehaviour::DAMAGE) {
			auto projIterator = projectiles.begin();
			while (!collisionDetected && !projectiles.empty() && projIterator != projectiles.end()) {

				float projX = (*projIterator)->getPosx();
				float projY = (*projIterator)->getPosy();
				float projZ = (*projIterator)->getPosz();

				//only check collisions if current collectibles is close enough to current projectile
				if ((currentX >= projX - 5 && currentX <= projX + 5) && (currentY >= projY - 5 && currentY <= projY + 5) && (currentZ >= projZ - 5 && currentZ <= projZ + 5)) {
					aiVector3D* projMin = new aiVector3D(0, 0, 0);
					aiVector3D* projMax = new aiVector3D(0, 0, 0);
					(*projIterator)->getHitbox(projMin, projMax);

					//build hitbox from min and max
					Hitbox projectileHitbox(*projMin, *projMax);

					if (bboxIntersection(projectileHitbox, collectibleHitbox)) {
						projIterator = projectiles.erase(projIterator);
						collIterator = collectibles.erase(collIterator);
						Context::getContext()->incrScore(1);
						AudioPlayer::playSound(POP_SOUND);
						collisionDetected = true;
					}

					delete projMin;
					delete projMax;

				}


				if (!collisionDetected) {
					projIterator++;
				}
			}
		}

		delete collMin;
		delete collMax;

		if (!collisionDetected) {
			collIterator++;
		}
	}




	delete playerMin;
	delete playerMax;
}

void PlayingState::spawnNewGround(){
	std::shared_ptr<ShapeObject> new_ground;
	std::shared_ptr<ShapeObject> lborder;
	std::shared_ptr<ShapeObject> rborder;
	std::shared_ptr<ShapeObject> linv;
	std::shared_ptr<ShapeObject> rinv;

	//ground default position
	float newX = 0;
	float newY = 0;
	float newZ = -10;

	bool considerPlayerPos = true;
	

	if (!grounds.empty()) { //if some ground objects were already created place new ground in contiguous way with respect to the last ground in the "grounds" vector
		considerPlayerPos = false;
		auto groundItr = grounds.end(); //iterator to the last element in ground list
		groundItr--;

		aiVector3D* prevMin = new aiVector3D(0, 0, 0);
		aiVector3D* prevMax = new aiVector3D(0, 0, 0);
		(*groundItr).ground->getHitbox(prevMin, prevMax); //get hitbox of ground that immediately precedes new ground

		newX = (*groundItr).ground->getPosx();
		newY = (*groundItr).ground->getPosy();
		newZ = (*groundItr).ground->getPosz() + (prevMax->z - prevMin->z); //get Z coordinate of previous ground and increase it by previous ground dimension along Z
		//by using the resulting value as new ground's Z coordinate the new ground will collide exactly with previous ground
	}

	new_ground = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, ModelRepository::getModel(SHELF_GROUND_ID)));
	new_ground->incrZSpeed(-1);
	objects.push_back(std::shared_ptr<GameObject>(new_ground));

	lborder = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, ModelRepository::getModel(SHELF_LBORDER_ID)));
	lborder->incrZSpeed(-1);
	objects.push_back(std::shared_ptr<GameObject>(lborder));

	rborder = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, ModelRepository::getModel(SHELF_RBORDER_ID)));
	rborder->incrZSpeed(-1);
	objects.push_back(std::shared_ptr<GameObject>(rborder));

	//invisible walls
	linv = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, ModelRepository::getModel(LINVISIBLE_WALL_ID)));
	linv->incrZSpeed(-1);
	collidables.push_back(std::shared_ptr<ShapeObject>(linv));

	rinv = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, ModelRepository::getModel(RINVISIBLE_WALL_ID)));
	rinv->incrZSpeed(-1);
	collidables.push_back(std::shared_ptr<ShapeObject>(rinv));

	grounds.push_back(GroundStruct(new_ground, lborder, rborder, linv, rinv));
}

void PlayingState::deleteGround(GroundStruct ground)
{

	auto objIterator = objects.begin();
	while (!objects.empty() && objIterator != objects.end()) {

		//check if pointers in ground struct and pointers in current position match, if so delete pointer from objects
		if (ground.ground.get() == (*objIterator).get() || ground.lborder.get() == (*objIterator).get() || ground.rborder.get() == (*objIterator).get()) {
			objIterator = objects.erase(objIterator);

		}
		else {
			objIterator++;
		}
	}

	auto collIterator = collidables.begin();
	while (!collidables.empty() && collIterator != collidables.end()) {

		//check if pointers in ground struct and pointers in current position match, if so delete pointer from collidables
		if (/*ground.lborder.get() == (*collIterator).get() || ground.rborder.get() == (*collIterator).get() ||*/ ground.linvisible.get() == (*collIterator).get() || ground.rinvisible.get() == (*collIterator).get()) {
			collIterator = collidables.erase(collIterator);
		}
		else {
			collIterator++;
		}
	}

	
}

void PlayingState::spawnProjectile() {
	std::shared_ptr<ShapeObject> projectile = std::make_shared<ShapeObject>(ShapeObject(player->getPosx(), player->getPosy(), player->getPosz(), ModelRepository::getModel(SWORD_PROJECTILE_ID), aiVector3D(1, 1, 1), PROJECTILE_SPEED));
	projectile->incrZSpeed(1);
	projectiles.emplace_back(projectile);
}

void PlayingState::displayUI() {
	glPushMatrix();
	setPerspMode(false);
	glDisable(GL_LIGHTING); //disable materials
	glLoadIdentity();
	gluLookAt(0, 0, -1, 0, 0, 0, 0, 1, 0);
	if (player->isShootActive()) {
		//if player has shooting powerup draw rectangle the length of which decreases based on powerup time left
		//color is red
		glPushMatrix();
		glLoadIdentity();

		float barlength = player->getRemainingTime(PowerupType::SHOOT);
		barlength = (barlength * UI_BAR_LENGTH) / SHOOT_POWER_DURATION;
		
		glColor3f(1, 0, 0);
		glBegin(GL_QUADS);
			glVertex2f(-(Context::getContext()->getWidth() / 2.f) + 10, (Context::getContext()->getHeight() / 2.f) - 10); //top left
			glVertex2f(-(Context::getContext()->getWidth() / 2.f) + 10 + barlength, (Context::getContext()->getHeight() / 2.f) - 10); //top right
			glVertex2f(-(Context::getContext()->getWidth() / 2.f) + 10 + barlength, (Context::getContext()->getHeight() / 2.f) - 35); //bottom right
			glVertex2f(-(Context::getContext()->getWidth() / 2.f) + 10, (Context::getContext()->getHeight() / 2.f) - 35); //bottom left
		glEnd();
		glPopMatrix();
	}

	if (player->isFlightActive()) {
		//if player has enhanced jump powerup draw rectangle the length of which decreases based on powerup time left
		//color is blue 
		glPushMatrix();
		glLoadIdentity();

		float barlength = player->getRemainingTime(PowerupType::FLIGHT);
		barlength = (barlength * UI_BAR_LENGTH) / FLIGHT_DURATION;

		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex2f(-(Context::getContext()->getWidth() / 2.f) + 10, (Context::getContext()->getHeight() / 2.f) - 45); //top left
		glVertex2f(-(Context::getContext()->getWidth() / 2.f) + 10 + barlength, (Context::getContext()->getHeight() / 2.f) - 45); //top right
		glVertex2f(-(Context::getContext()->getWidth() / 2.f) + 10 + barlength, (Context::getContext()->getHeight() / 2.f) - 70); //bottom right
		glVertex2f(-(Context::getContext()->getWidth() / 2.f) + 10, (Context::getContext()->getHeight() / 2.f) - 70); //bottom left
		glEnd();
		glPopMatrix();
	}

	//draw score
	aiVector3D* min = new aiVector3D(0, 0, 0);
	aiVector3D* max = new aiVector3D(0, 0, 0);
	glColor3f(0, 0, 0);

	//get a pointer to desired model and get its size
	std::shared_ptr<Model> backgroundModel = ModelRepository::getModel(EMPTY_YELLOW);
	backgroundModel->getHitbox(min, max);

	glPushMatrix();
	std::string out = "SCORE: " + std::to_string(Context::getContext()->getScore());
	int textWidth = glutBitmapLength(FONT, (unsigned char*)out.c_str());
	float xPos = (textWidth / (2.f * Context::getContext()->getWidth()) + textWidth / 2.f);
	float yPos = (FONT_HEIGHT / (2.f * Context::getContext()->getHeight()) + (Context::getContext()->getHeight() / 2.f) - (FONT_HEIGHT + 10));

	float xScale = Context::getContext()->getScaleForTarget(textWidth + 50, max->x - min->x);
	float yScale = Context::getContext()->getScaleForTarget(FONT_HEIGHT + 20, max->y - min->y);
	glEnable(GL_LIGHTING);
	backgroundModel->display(xPos - textWidth * .5, yPos + FONT_HEIGHT / 2.f, 0, aiVector3D(xScale, yScale, 1));
	glDisable(GL_LIGHTING);
	output(xPos, yPos, out);
	glPopMatrix();
	glEnable(GL_LIGHTING); //re-enable materials

	//draw hearts
	float scaleFactor = Context::getContext()->getScaleFactor();
	std::shared_ptr<Model> heart = ModelRepository::getModel(HEART_ID);
	//glBegin(GL_POLYGON);
	glPushMatrix();
	glScalef(1 / scaleFactor, 1 / scaleFactor, 1 / scaleFactor);
	yPos = (Context::getContext()->getHeight() * scaleFactor / 2.f) - 20 * scaleFactor; //defines an offest along y-axis from the top border of the window
	for (int i = 0; i < player->getLives(); i++) {
		float xPos = scaleFactor*((-Context::getContext()->getWidth()/ 2.f) + 20 + 40 * i); //defines an offest along x-axis from the right border of the window
		heart->display(xPos, yPos, 0);
	}
	glPopMatrix();

	
	setPerspMode(true);
	glPopMatrix();
	delete (min, max);
}

