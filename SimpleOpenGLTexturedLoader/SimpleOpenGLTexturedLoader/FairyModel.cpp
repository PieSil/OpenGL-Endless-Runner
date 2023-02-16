#include "FairyModel.h"
#include "GLutils.h"
#include "Timer.h"
#include "Const.h"

FairyModel::FairyModel(float wingsAngle) : wingsAngle(wingsAngle) {
	wingSpeed = FAIRY_WING_SPEED;
	wingsDown = true;
}

void FairyModel::display(float x, float y, float z, aiVector3D scale, bool ortho) {
		aiVector3D* min = new aiVector3D(0, 0, 0);
		aiVector3D* max = new aiVector3D(0, 0, 0);

		glPushMatrix();
		//glLoadIdentity();
		glTranslatef(x, y, z);
		glScalef(1/scale.x, 1/scale.y, 1/scale.z);
		recursive_render(scene, scene->mRootNode->mChildren[FAIRY_ID], 1.0);  //!!IMPORTANT: rendered object depends on the order of the objects inside the imported scene
																			  //this specific call should render a fairy
		glPopMatrix();

		glPushMatrix();
		//glLoadIdentity();
		glTranslatef(x, y, z);
		glRotatef(wingsAngle, 0., 0., 1.);
		glScalef(scale.x, scale.y, scale.z);
		recursive_render(scene, scene->mRootNode->mChildren[LWINGS_ID], 1.0);
		glPopMatrix();

		glPushMatrix();
		//glLoadIdentity();
		glTranslatef(x, y, z);
		glRotatef(-1 * wingsAngle, 0., 0., 1.);
		glScalef(scale.x, scale.y, scale.z);
		recursive_render(scene, scene->mRootNode->mChildren[RWINGS_ID], 1.0);
		glPopMatrix();

		///*draw hitbox*/

		//getHitbox(min, max);

		//min->x += x;
		//min->y += y;
		//min->z += z;

		//max->x += x;
		//max->y += y;
		//max->z += z;

		////hitbox left face
		//glBegin(GL_POLYGON);
		//glVertex3f(min->x, min->y, min->z);
		//glVertex3f(min->x, min->y, max->z);
		//glVertex3f(min->x, max->y, max->z);
		//glVertex3f(min->x, max->y, min->z);
		//glEnd();

		////hitbox right face
		//glBegin(GL_POLYGON);
		//glVertex3f(max->x, min->y, min->z);
		//glVertex3f(max->x, max->y, min->z);
		//glVertex3f(max->x, max->y, max->z);
		//glVertex3f(max->x, min->y, max->z);
		//glEnd();

		////hitbox bottom face
		//glBegin(GL_POLYGON);
		//glVertex3f(min->x, min->y, min->z);
		//glVertex3f(min->x, min->y, max->z);
		//glVertex3f(max->x, min->y, max->z);
		//glVertex3f(max->x, min->y, min->z);
		//glEnd();

		////hitbox top face
		//glBegin(GL_POLYGON);
		//glVertex3f(min->x, max->y, max->z);
		//glVertex3f(min->x, max->y, min->z);
		//glVertex3f(max->x, max->y, min->z);
		//glVertex3f(max->x, max->y, max->z);
		//glEnd();

		////hitbox back face
		//glBegin(GL_POLYGON);
		//glVertex3f(min->x, min->y, min->z);
		//glVertex3f(min->x, max->y, min->z);
		//glVertex3f(max->x, max->y, min->z);
		//glVertex3f(max->x, min->y, min->z);
		//glEnd();

		////hitbox front face
		//glBegin(GL_POLYGON);
		//glVertex3f(min->x, max->y, max->z);
		//glVertex3f(min->x, min->y, max->z);
		//glVertex3f(max->x, min->y, max->z);
		//glVertex3f(max->x, max->y, max->z);
		//glEnd();


		delete min;
		delete max;
}

void FairyModel::animate()
{
	//move wings based on how much time has passed since last iteration
	double elapsedTime = Timer::getTimer()->getElapsed();
	if (wingsDown) {
		wingsAngle += wingSpeed * elapsedTime;
		if (wingsAngle >= 40)
			wingsDown = false;
	}
	else {
		wingsAngle -= wingSpeed * elapsedTime;
		if (wingsAngle <= 0)
			wingsDown = true;
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
	//mul4x4ByPoint(trasformationMatrix, &(min->x), &(min->y), &(min->z), &w);
	//mul4x4ByPoint(trasformationMatrix, &(max->x), &(max->y), &(max->z), &w);
}
