#pragma once
#include "Model.h"
class AssimpModel :
    public Model
{
public:
	explicit AssimpModel(int childId, bool rotate = false);

	void display(float x, float y, float z) override;
	void getHitbox(struct aiVector3D* min, struct aiVector3D* max) override;
	void animate() override;

protected:
	int childId;
	bool rotate;
	double angle;
	double rotationSpeed;
};

