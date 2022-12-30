#pragma once
#include "Model.h"
class AssimpModel :
    public Model
{
public:
	explicit AssimpModel(int childrenId);

	void display(float x, float y, float z) override;
	void animate() {};
	void getHitbox(struct aiVector3D* min, struct aiVector3D* max) override;

protected:
	int childrenId;
};

