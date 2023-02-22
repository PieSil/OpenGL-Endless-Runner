#include "AssimpModel.h"
#include "Const.h"
#include "Timer.h"

AssimpModel::AssimpModel(int childId, bool rotate) : childId(childId), rotate(rotate) {
	angle = 0.0;
	rotationSpeed = MODEL_ROTATION_SPEED;
}

void AssimpModel::display(float x, float y, float z, aiVector3D scale) {
	aiVector3D* min = new aiVector3D(0, 0, 0);
	aiVector3D* max = new aiVector3D(0, 0, 0);


	glPushMatrix();
	glTranslatef(x, y, z);
	if (rotate) {
		glRotatef(angle, 0., 1., 0.);
	}
	glScalef(1/scale.x, 1/scale.y, 1/scale.z);
	recursive_render(scene, scene->mRootNode->mChildren[childId], 1.0);  //!!IMPORTANT: rendered object depends on the order of the objects inside the imported scene
	glPopMatrix();

	delete min;
	delete max;
}

void AssimpModel::getHitbox(aiVector3D* min, aiVector3D* max) {
	//copied from GLUtils.h

	struct aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);
	float w = 1;

	min->x = min->y = min->z = 1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode->mChildren[childId], min, max, &trafo);
}

void AssimpModel::animate(){
	if (rotate) {
		//rotates model on the spot
		double elapsedTime = Timer::getTimer()->getElapsed();
		angle += rotationSpeed * elapsedTime;
		if (angle >= 360)
			angle -= 360;
	}
}
