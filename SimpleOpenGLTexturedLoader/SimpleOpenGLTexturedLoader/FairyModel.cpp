#include "FairyModel.h"
#include "GLutils.h"
#include "Timer.h"
#include "Const.h"

FairyModel::FairyModel(float wingsAngle) : wingsAngle(wingsAngle) {
	wingSpeed = FAIRY_WING_SPEED;
	wingsDown = true;
}

void FairyModel::display(float x, float y, float z, aiVector3D scale) {
		aiVector3D* min = new aiVector3D(0, 0, 0);
		aiVector3D* max = new aiVector3D(0, 0, 0);


		//display fairy body
		glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(1/scale.x, 1/scale.y, 1/scale.z);
		recursive_render(scene, scene->mRootNode->mChildren[FAIRY_ID], 1.0);  //!!IMPORTANT: rendered object depends on the order of the objects inside the imported scene																	  //this specific call should render a fairy
		glPopMatrix();


		//display left wings
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(wingsAngle, 0., 0., 1.);
		glScalef(scale.x, scale.y, scale.z);
		recursive_render(scene, scene->mRootNode->mChildren[LWINGS_ID], 1.0);
		glPopMatrix();


		//display right wings
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(-1 * wingsAngle, 0., 0., 1.);
		glScalef(scale.x, scale.y, scale.z);
		recursive_render(scene, scene->mRootNode->mChildren[RWINGS_ID], 1.0);
		glPopMatrix();

		delete min;
		delete max;
}

void FairyModel::animate()
{
	//move wings based on how much time has passed since last iteration
	double elapsedTime = Timer::getTimer()->getElapsed();
	if (wingsDown) {
		wingsAngle += wingSpeed * elapsedTime;
		if (wingsAngle > 40) {
			wingsAngle = 40;
			wingsDown = false;
		}
	}
	else {
		wingsAngle -= wingSpeed * elapsedTime;
		if (wingsAngle < 0) {
			wingsAngle = 0;
			wingsDown = true;
		}
	}

}

void FairyModel::getHitbox(struct aiVector3D* min, struct aiVector3D* max){
	//copied from GLUtils.h

	struct aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);
	float w = 1;

	min->x = min->y = min->z = 1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode->mChildren[0], min, max, &trafo);
}
