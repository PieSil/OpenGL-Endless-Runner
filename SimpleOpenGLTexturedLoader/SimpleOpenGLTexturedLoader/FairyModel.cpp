#include "FairyModel.h"
#include "GLutils.h"
#include "Timer.h"

FairyModel::FairyModel(float wingsAngle) : wingsAngle(wingsAngle) {
	wingSpeed = 0.1;
	wingsDown = true;
}

void FairyModel::display(float x, float y, float z) {

		glPushMatrix();
		//glLoadIdentity();
		glTranslatef(x, y, z);
		recursive_render(scene, scene->mRootNode->mChildren[0], 1.0);  //!!IMPORTANT: rendered object depends on the order of the objects inside the imported scene
																	   //this specific call should render a fairy
		glPopMatrix();
		glPushMatrix();
		//glLoadIdentity();
		glTranslatef(x, y, z);
		glRotatef(wingsAngle, 0., 0., 1.);
		recursive_render(scene, scene->mRootNode->mChildren[1], 1.0);
		glPopMatrix();
		glPushMatrix();
		//glLoadIdentity();
		glTranslatef(x, y, z);
		glRotatef(-1 * wingsAngle, 0., 0., 1.);
		recursive_render(scene, scene->mRootNode->mChildren[2], 1.0);
		glPopMatrix();
}

void FairyModel::animate()
{
	//move wings based on how much time has passed since last iteration
	double elapsedTime = Timer::getTimer()->getElapsed();
	if (wingsDown) {
		wingsAngle += wingSpeed * elapsedTime;
		if (wingsAngle >= 45)
			wingsDown = false;
	}
	else {
		wingsAngle -= wingSpeed * elapsedTime;
		if (wingsAngle <= 0)
			wingsDown = true;
	}

}
