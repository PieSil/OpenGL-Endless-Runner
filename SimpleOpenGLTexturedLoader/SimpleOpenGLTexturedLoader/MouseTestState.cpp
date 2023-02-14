#include "MouseTestState.h";
#include "ModelRepository.h";
#include "Context.h";
#include "Hitbox.h";

void MouseTestState::display()
{
	glPushMatrix();
	float scaleFactor = Context::getContext()->getScaleFactor();
	scaleFactor *= 0.05;
	glScalef(1 / scaleFactor, 1 / scaleFactor, 1 / scaleFactor);
	GameState::display();
	rect.display();
	glPopMatrix();
}

void MouseTestState::handleInput(unsigned char key, int x, int y)
{
	//aiVector3D* v1 = new aiVector3D(0,0,0);
	//aiVector3D* v2 = new aiVector3D(0, 0, 0);
	//rect.getHitbox(v1, v2);
	//float scaleFactor = Context::getContext()->getScaleFactor();
	//scaleFactor *= 0.05;
	//*v1 = *v1 / scaleFactor;
	//*v2 = *v2 / scaleFactor;
	//Hitbox h = Hitbox(*v1, *v2);
	//if (mouseBboxIntersection(x, y, h)) {
	//	// change model
	//	rect.setModel(ModelRepository::getModel(RED_RECTANGLE_ID).get());
	//}
	//else {
	//	// put white one
	//}
	//delete(v1, v2);
}

MouseTestState::MouseTestState(GameLogic* pointer, bool persp): GameState(pointer, persp), 
rect(ShapeObject(0, 0, 0, ModelRepository::getModel(HEART_ID)))
{
	/*auto obj = std::make_shared<ShapeObject>(ShapeObject(0, 0, 0, ModelRepository::getModel(WHITE_RECTAGLE_ID)));
	objects.push_back(obj);*/
}

void MouseTestState::mouseMotion(int x, int y)
{
	aiVector3D* v1 = new aiVector3D(0, 0, 0);
	aiVector3D* v2 = new aiVector3D(0, 0, 0);
	rect.getHitbox(v1, v2);
	float scaleFactor = Context::getContext()->getScaleFactor();
	scaleFactor *= 0.05;
	*v1 = *v1 / scaleFactor;
	*v2 = *v2 / scaleFactor;
	Hitbox h = Hitbox(*v1, *v2);
	if (mouseBboxIntersection(x - Context::getContext()->getWidth()/2, 
		y - Context::getContext()->getHeight() / 2, h)) {
		// change model
		rect.setModel(ModelRepository::getModel(RED_RECTANGLE_ID));
	}
	else {
		// put white one
		rect.setModel(ModelRepository::getModel(HEART_ID));
	}
	delete(v1, v2);
}
