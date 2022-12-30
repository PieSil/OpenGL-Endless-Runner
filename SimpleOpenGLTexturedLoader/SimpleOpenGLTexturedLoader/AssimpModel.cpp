#include "AssimpModel.h"

AssimpModel::AssimpModel(int childrenId) : childrenId(childrenId) {}

void AssimpModel::display(float x, float y, float z) {
	aiVector3D* min = new aiVector3D(0, 0, 0);
	aiVector3D* max = new aiVector3D(0, 0, 0);

	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(x, y, z);
	recursive_render(scene, scene->mRootNode->mChildren[childrenId], 1.0);  //!!IMPORTANT: rendered object depends on the order of the objects inside the imported scene
																   //this specific call should render a fairy
	glPopMatrix();

	/*draw hitbox*/

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

void AssimpModel::getHitbox(aiVector3D* min, aiVector3D* max) {
	struct aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);
	float w = 1;

	min->x = min->y = min->z = 1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode->mChildren[childrenId], min, max, &trafo);
}
