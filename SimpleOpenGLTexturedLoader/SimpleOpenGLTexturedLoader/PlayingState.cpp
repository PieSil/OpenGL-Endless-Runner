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

PlayingState::PlayingState(GameLogic* game) : GameState(game) {
	//player = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, std::make_shared<CubeModel>(CubeModel(1)), 0.25));
	player = std::make_shared<PhysicalObject>(PhysicalObject(0, 1, -5, std::make_shared<FairyModel>(FairyModel()), .25));
	objects.push_back(std::shared_ptr<GameObject>(player));
	//collidables.push_back(std::shared_ptr<ShapeObject>(player));

	//test cube
	std::shared_ptr<ShapeObject> test_cube = std::make_shared<ShapeObject>(ShapeObject(0, 0, -10, std::make_shared<AssimpModel>(AssimpModel(TEST_SPHERE_ID))));
	objects.push_back(std::shared_ptr<GameObject>(test_cube));
	collidables.push_back(std::shared_ptr<ShapeObject>(test_cube));

	//ground
	ground = std::make_shared<ShapeObject>(ShapeObject(0, 0, -10, std::make_shared<AssimpModel>(AssimpModel(GROUND_ID))));
	objects.push_back(std::shared_ptr<GameObject>(ground));
	//collidables.push_back(std::shared_ptr<ShapeObject>(ground));

	
	std::shared_ptr<ShapeObject> lborder = std::make_shared<ShapeObject>(ShapeObject(0, 0, -10, std::make_shared<AssimpModel>(AssimpModel(LBORDER_ID))));
	objects.push_back(std::shared_ptr<GameObject>(lborder));
	collidables.push_back(std::shared_ptr<ShapeObject>(lborder));

	

	std::shared_ptr<ShapeObject> rborder = std::make_shared<ShapeObject>(ShapeObject(0, 0, -10, std::make_shared<AssimpModel>(AssimpModel(RBORDER_ID))));
	objects.push_back(std::shared_ptr<GameObject>(rborder));
	collidables.push_back(std::shared_ptr<ShapeObject>(rborder));

	
	//invisible walls
	std::shared_ptr<ShapeObject> linv = std::make_shared<ShapeObject>(ShapeObject(0, 0, -10, std::make_shared<AssimpModel>(AssimpModel(LINVISIBLE_WALL_ID))));
	collidables.push_back(std::shared_ptr<ShapeObject>(linv));

	std::shared_ptr<ShapeObject> rinv = std::make_shared<ShapeObject>(ShapeObject(0, 0, -10, std::make_shared<AssimpModel>(AssimpModel(RINVISIBLE_WALL_ID))));
	collidables.push_back(std::shared_ptr<ShapeObject>(rinv));
	


}

void PlayingState::update() {
	GameState::update();
	//check collisions
	checkCollisions();
}

void PlayingState::handleInput(unsigned char key) {
	//manages inputs, should depend on active state
	
	switch (key) {
	case 'w': case 'W':
		player->move(0, 0, 1.0);
		break;
	case 's': case 'S':
		player->move(0, 0, -1.0);
		break;
	case 'a': case 'A':
		player->move(1, 0, 0);
		break;
	case 'd': case 'D':
		player->move(-1, 0, 0);
		break;
	case ' ': case 'r':
		if (player->isOnGround()) {
			player->setVertSpeed(0.015);
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
	case 'c': case 'C':
		game->setState(State::TEST);
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
			a.min.x < b.max.x &&
			a.max.x > b.min.x &&
			a.min.y < b.max.y &&
			a.max.y > b.min.y &&
			a.min.z < b.max.z &&
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

		//only check hitboxes if objects are close enough DO NOT USE THIS IF CLAUSE TO TEST FOR MAP COLLISIONS (can maybe be used for collectibles/hazards)
		// //currently this if clause is not enbaled
		//if ((currentX >= playerX - 1 && currentX <= playerX + 1) && (currentY >= playerY - 1 && currentY <= playerY + 1) && (currentZ >= playerZ - 1 && currentZ <= playerZ + 1)) {

		aiVector3D* currentMin = new aiVector3D(0, 0, 0);
		aiVector3D* currentMax = new aiVector3D(0, 0, 0);
		current->getHitbox(currentMin, currentMax);

		//build hitbox from min and max
		Hitbox collidableHitbox(*currentMin, *currentMax);

		if (bboxIntersection(playerHitbox, collidableHitbox)) {
			printf("Player colliding with an object\n");
			//Collision detected, manage collision

			//leave like this for now, elaborate collision resolution only if needed
			player->revertMovement();
		}

		delete currentMin;
		delete currentMax;
		//}
	}

	if (!player->isOnGround()) {  //if player is not onGround also check collision with ground
		aiVector3D* groundMin = new aiVector3D(0, 0, 0);
		aiVector3D* groundMax = new aiVector3D(0, 0, 0);
		ground->getHitbox(groundMin, groundMax);
		Hitbox groundHitbox = Hitbox(*groundMin, *groundMax);

		if (bboxIntersection(playerHitbox, groundHitbox)) {
			player->revertMovement(false, true, false); //revert movement only on y axis
			player->setOnGround(true);
			player->setVertSpeed(0);
		}
		delete groundMin;
		delete groundMax;
	}


	delete playerMin;
	delete playerMax;
}
