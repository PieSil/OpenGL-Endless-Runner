#include "FairyModel.h"
#include "GLutils.h"
#include "Timer.h"

FairyModel::FairyModel(float wingsAngle) : wingsAngle(wingsAngle) {
	wingSpeed = 0.1;
	wingsDown = true;
}

void FairyModel::display(float x, float y, float z)
{
	//if(scene_list == 0) {
            // now begin at the root node of the imported data and traverse
            // the scenegraph by multiplying subsequent local transforms
            // together on GL's matrix stack.
		//animate();

	//x *= -1;
	//y *= -1;
	//z *= -1;
		
		//glLoadIdentity();
		glPushMatrix();
		//glLoadIdentity();
		//glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glTranslatef(x, y, z);
		recursive_render(scene, scene->mRootNode->mChildren[0], 1.0);
		glPopMatrix();
		glPushMatrix();
		//glLoadIdentity();
		glRotatef(wingsAngle, 0., 0., 1.);
		glTranslatef(x, y, z);
		recursive_render(scene, scene->mRootNode->mChildren[1], 1.0);
		glPopMatrix();
		glPushMatrix();
		//glLoadIdentity();
		glRotatef(-1 * wingsAngle, 0., 0., 1.);
		glTranslatef(x, y, z);
		recursive_render(scene, scene->mRootNode->mChildren[2], 1.0);
		glPopMatrix();
		glPopMatrix();
		
	//}
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
