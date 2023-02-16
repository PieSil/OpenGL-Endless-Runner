#include "Hitbox.h"

bool bboxIntersection(Hitbox a, Hitbox b) {
	//return true if a and b intersect
	bool result = (
		a.min.x < b.max.x&&
		a.max.x > b.min.x &&
		a.min.y < b.max.y&&
		a.max.y > b.min.y &&
		a.min.z < b.max.z&&
		a.max.z > b.min.z
		);

	return result;
}

bool mouseBboxIntersection(int x, int y, Hitbox h) {
	return x > h.min.x && x < h.max.x&&
		y< h.max.y&& y> h.min.y;
}