#include "GameObject.h"
#include <GL/glut.h>
#include "Timer.h"
#include "Context.h"
#include <iostream>
GameObject::GameObject(float x, float y, float z, float _speed) : pos_x(x), pos_y(y), pos_z(z), prev_x(x), prev_y(y), prev_z(z), speed(_speed), xSpeed(0), ySpeed(0), zSpeed(0) {}

void GameObject::update() {
	//do nothing by default
	//override if a certain behaviour needs to be applied
}

void GameObject::move() {
	//recover elapsed time since last iteration
	double elapsedTime = Timer::getTimer()->getElapsed(); 
	double scaleFactor = Context::getContext()->getScaleFactor();
	std::cout << "Elapsed true output " << elapsedTime << "\n";


	//save previous position, used for collision resolution
	prev_x = pos_x;
	prev_y = pos_y;
	prev_z = pos_z;

	//move based on how much time has passed since last iteration, makes movement independent from FPS  <--- VERY IMPORTANT
	pos_x += elapsedTime * speed * xSpeed;
	pos_y += elapsedTime * speed * ySpeed;
	pos_z += elapsedTime * speed * zSpeed;
}

void GameObject::revertMovement(bool x, bool y, bool z ) {
	//used in collision resolution, revert position to previous one

	if (x)
		pos_x = prev_x;

	if (y)
		pos_y = prev_y;

	if(z)
		pos_z = prev_z;
}
