#include "GameObject.h"
#include <GL/glut.h>
#include "Timer.h"
#include <iostream>
GameObject::GameObject(float x, float y, float z, float _speed) : pos_x(x), pos_y(y), pos_z(z), speed(_speed) {}

void GameObject::update() {
	//do nothing by default
	//override if a certain behaviour needs to be applied
}

void GameObject::move(float x, float y, float z) {
	//recover elapsed time since last iteration
	double elapsedTime = Timer::getTimer()->getElapsed(); 
	//move based on how much time has passed since last iteration, makes movement independent from FPS
	if (elapsedTime != 0) {
		std::cout << "moving";
	}
	pos_x += elapsedTime * speed * x;
	pos_y += elapsedTime * speed * y;
	pos_z += elapsedTime * speed * z;
}
