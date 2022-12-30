#pragma once
#include "GLutils.h"

//Abstract class which offers two methods used for rendering of different models, 
//if model is not animated just ignore the animate() method

class Model {
public:
	explicit Model();

	virtual void display(float x, float y, float z) = 0;
	virtual void animate() {};
	virtual void getHitbox(struct aiVector3D* min, struct aiVector3D* max) = 0;
};

