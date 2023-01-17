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

#define COLL_DESPAWN_Z -12

PlayingState::PlayingState(GameLogic* game) : GameState(game) {

	pointsToNextAccel = 20;

	//reset game score
	Context::getContext()->resetScore();

	//set game speed
	Context::getContext()->setGameSpeed(10);
	collectibleSpawner = CollectibleSpawner();

	//create player object and add it to renderable objects
	player = std::make_shared<PlayerObject>(PlayerObject(0, 3, -5, std::make_shared<FairyModel>(FairyModel()), 10));
	objects.push_back(std::shared_ptr<GameObject>(player));



	////test cube
	//std::shared_ptr<ShapeObject> test_cube = std::make_shared<ShapeObject>(ShapeObject(0, 0, -10, std::make_shared<AssimpModel>(AssimpModel(TEST_SPHERE_ID))));
	//objects.push_back(std::shared_ptr<GameObject>(test_cube));
	//collidables.push_back(std::shared_ptr<ShapeObject>(test_cube));
	
	//create sample collectibles
	/*collectibles.push_back(std::make_shared<CollectibleObject>(CollectibleObject(0, 0, 5, std::make_shared<AssimpModel>(AssimpModel(POINT_SPHERE_ID)), COL_SPEED, CollectibleBehaviour::POINT)));
	collectibles.push_back(std::make_shared<CollectibleObject>(CollectibleObject(2, 0, 12, std::make_shared<AssimpModel>(AssimpModel(SPIKEBALL_ID)), COL_SPEED, CollectibleBehaviour::DAMAGE)));
	collectibles.push_back(std::make_shared<CollectibleObject>(CollectibleObject(-2, 0, 12, std::make_shared<AssimpModel>(AssimpModel(POWER1_ID)), COL_SPEED, CollectibleBehaviour::POWERUP1)));*/

	for (auto coll : collectibles) {
		coll->incrZSpeed(-1);
	}
}

void PlayingState::display(){
	//call GameState display() function in order to render all elements in "object" list
	GameState::display();

	//then render all collectibles
	for (auto coll = collectibles.begin(); coll != collectibles.end(); coll++) {
		(*coll)->display();
	}
}

void PlayingState::update() {
	if (pointsToNextAccel - Context::getContext()->getScore() <= 0) {
		pointsToNextAccel += 20;
		Context::getContext()->incrGameSpeed(2);
	}
	//spawn ground, must be placed here because if placed in constructor may create some problems with Assimp
	if (grounds.empty()) {
		spawnNewGround();
		spawnNewGround();
		spawnNewGround();
	}

	auto newCollectibles = collectibleSpawner.spawnCollectibles();

	if (!newCollectibles.empty()) {
		for (std::shared_ptr<CollectibleObject> coll : newCollectibles) {
			collectibles.push_back(coll);
		}
	}

	auto collIterator = collectibles.begin();
	while (!collectibles.empty() && collIterator != collectibles.end()) {
		
		//move collectibles
		(*collIterator)->move(Context::getContext()->getGameSpeed());

		//check if collectible is too far back along Z, in that case destroy it
		if ((*collIterator)->getPosz() <= COLL_DESPAWN_Z) {
			collIterator = collectibles.erase(collIterator);

		} else {
			collIterator++;
		}
	}

	player->move();
	GameState::update();

	//check collisions
	checkCollisions();

	//check player status:
	if (player->getLives() <= 0) {
		game->setState(State::TEST); //replace with game over state
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
	case 'a': case 'A':
		if (player->isOnGround()) {
			player->incrXSpeed(1.);
			player->setInputRecorded(true);
		}
		break;
	case 'd': case 'D':
		if (player->isOnGround()) {
			player->incrXSpeed(-1.);
			player->setInputRecorded(true);
		}
		break;
	case ' ': case 'r':
		if (player->isOnGround()) {
			player->setInputRecorded(false);
			player->resetXSpeed();
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
		if (player->isOnGround() && player->isInputRecorded()) {
			player->incrXSpeed(-1.);
			//player->setInputRecorded(false);
		}

		break;
	case 'd': case 'D':
		if (player->isOnGround() && player->isInputRecorded()) {
			player->incrXSpeed(1.);
			//player->setInputRecorded(false);
		}
		break;
	default:
		break;
	}
}

void PlayingState::checkCollisions() {
	//check all relevant collisions between objects in current level e. g. player and ground, player and collectible items


	struct HitboxVertex {
		//defines a vertex
		HitboxVertex(int x, int y, int z) : x(x), y(y), z(z) {};
		HitboxVertex() : x(0), y(0), z(0) {};

		int x;
		int y;
		int z;
	};

	struct HitboxFace {
		//defines a hitbox face (separating a bounding box into its 6 faces may be useful to solve collisions with respecto to the direction of the collision)
		HitboxFace(HitboxVertex p1, HitboxVertex p2, HitboxVertex p3, HitboxVertex p4) : p1(p1), p2(p2), p3(p3), p4(p4), vertices() {
			vertices[0] = p1;
			vertices[1] = p2;
			vertices[2] = p3;
			vertices[3] = p4;
		};

		HitboxFace() {}

		HitboxVertex p1;
		HitboxVertex p2;
		HitboxVertex p3;
		HitboxVertex p4;
		HitboxVertex vertices[4];
	};

	struct Hitbox {
		//defines a hitbox
		Hitbox(aiVector3D min, aiVector3D max, HitboxFace left, HitboxFace right, HitboxFace top, HitboxFace bottom, HitboxFace front, HitboxFace back) :
			min(min), max(max), left(left), right(right), top(top), bottom(bottom), front(front), back(back) {};
		Hitbox(aiVector3D min, aiVector3D max) : min(min), max(max) {

			left = HitboxFace(HitboxVertex(min.x, min.y, min.z),
				HitboxVertex(min.x, min.y, max.z),
				HitboxVertex(min.x, max.y, max.z),
				HitboxVertex(min.x, max.y, min.z));

			right = HitboxFace(HitboxVertex(max.x, min.y, min.z),
				HitboxVertex(max.x, min.y, max.z),
				HitboxVertex(max.x, max.y, max.z),
				HitboxVertex(max.x, max.y, min.z));

			bottom = HitboxFace(HitboxVertex(min.x, min.y, min.z),
				HitboxVertex(max.x, min.y, min.z),
				HitboxVertex(max.x, min.y, max.z),
				HitboxVertex(min.x, min.y, max.z));

			top = HitboxFace(HitboxVertex(min.x, max.y, min.z),
				HitboxVertex(max.x, max.y, min.z),
				HitboxVertex(max.x, max.y, max.z),
				HitboxVertex(min.x, max.y, max.z));

			back = HitboxFace(HitboxVertex(min.x, min.y, min.z),
				HitboxVertex(max.x, min.y, min.z),
				HitboxVertex(max.x, max.y, min.z),
				HitboxVertex(min.x, max.y, min.z));

			front = HitboxFace(HitboxVertex(min.x, min.y, max.z),
				HitboxVertex(max.x, min.y, max.z),
				HitboxVertex(max.x, max.y, max.z),
				HitboxVertex(min.x, max.y, max.z));
		}

		aiVector3D min;
		aiVector3D max;

		HitboxFace left;
		HitboxFace right;
		HitboxFace top;
		HitboxFace bottom;
		HitboxFace front;
		HitboxFace back;
	};

	auto bboxIntersection = [](Hitbox a, Hitbox b) {
		//return true if a and b intersect
		bool result = (
			a.min.x < b.max.x&&
			a.max.x > b.min.x &&
			a.min.y < b.max.y&&
			a.max.y > b.min.y &&
			a.min.z < b.max.z&&
			a.max.z > b.min.z
			);

		return result;
	};

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
			currentGround->getHitbox(groundMin, groundMax);
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

		//only check hitboxes if objects are close enough
		if ((currentX >= playerX - 5 && currentX <= playerX + 5) && (currentY >= playerY - 5 && currentY <= playerY + 5) && (currentZ >= playerZ - 5 && currentZ <= playerZ + 5)) {

			aiVector3D* collMin = new aiVector3D(0, 0, 0);
			aiVector3D* collMax = new aiVector3D(0, 0, 0);
			(*collIterator)->getHitbox(collMin, collMax);

			//build hitbox from min and max
			Hitbox collectibleHitbox(*collMin, *collMax);

			if (bboxIntersection(playerHitbox, collectibleHitbox)) {
				//if a collision is detected apply the collectible effect to player, then erase the collectible
				//collIterator MUST NOT be updated during this iteration
				printf("Player collided with collectible\n");
				(*collIterator)->applyEffect(player.get());
				collIterator = collectibles.erase(collIterator);
				collisionDetected = true;
			}

			delete collMin;
			delete collMax;
		} 

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
	std::list<std::shared_ptr<CollectibleObject>> newCollectibles;

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
		(*groundItr)->getHitbox(prevMin, prevMax); //get hitbox of ground that immediately precedes new ground

		newX = (*groundItr)->getPosx();
		newY = (*groundItr)->getPosy();
		newZ = (*groundItr)->getPosz() + (prevMax->z - prevMin->z); //get Z coordinate of previous ground and increase it by previous ground dimension along Z
		//by using the resulting value as new ground's Z coordinate the new ground will collide exactly with previous ground
	}

	new_ground = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, std::make_shared<AssimpModel>(AssimpModel(GROUND_ID))));
	grounds.push_back(new_ground);
	objects.push_back(std::shared_ptr<GameObject>(new_ground));

	lborder = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, std::make_shared<AssimpModel>(AssimpModel(LBORDER_ID))));
	objects.push_back(std::shared_ptr<GameObject>(lborder));
	collidables.push_back(std::shared_ptr<ShapeObject>(lborder));

	rborder = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, std::make_shared<AssimpModel>(AssimpModel(RBORDER_ID))));
	objects.push_back(std::shared_ptr<GameObject>(rborder));
	collidables.push_back(std::shared_ptr<ShapeObject>(rborder));

		//invisible walls
	linv = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, std::make_shared<AssimpModel>(AssimpModel(LINVISIBLE_WALL_ID))));
	collidables.push_back(std::shared_ptr<ShapeObject>(linv));

	rinv = std::make_shared<ShapeObject>(ShapeObject(newX, newY, newZ, std::make_shared<AssimpModel>(AssimpModel(RINVISIBLE_WALL_ID))));
	collidables.push_back(std::shared_ptr<ShapeObject>(rinv));

	/*newCollectibles = collectibleSpawner.getCollectibles(aiVector3D(player->getPosx(), player->getPosy(), player->getPosz()), aiVector3D(new_ground->getPosx(), new_ground->getPosy(), new_ground->getPosz()), considerPlayerPos);

	for (std::shared_ptr<CollectibleObject> coll : newCollectibles) {
		collectibles.push_back(coll);
	}*/

}
