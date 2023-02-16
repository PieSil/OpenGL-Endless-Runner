#pragma once
#include "GLutils.h"

struct HitboxVertex {
	//defines a vertex
	HitboxVertex(int x, int y, int z) : x(x), y(y), z(z) {};
	HitboxVertex() : x(0), y(0), z(0) {};

	int x;
	int y;
	int z;
};

struct HitboxFace {
	//defines a hitbox face (separating a bounding box into its 6 faces may be useful to solve collisions with respecto to the direction of the collision)
	HitboxFace(HitboxVertex p1, HitboxVertex p2, HitboxVertex p3, HitboxVertex p4) : p1(p1), p2(p2), p3(p3), p4(p4), vertices() {
		vertices[0] = p1;
		vertices[1] = p2;
		vertices[2] = p3;
		vertices[3] = p4;
	};

	HitboxFace() {}

	HitboxVertex p1;
	HitboxVertex p2;
	HitboxVertex p3;
	HitboxVertex p4;
	HitboxVertex vertices[4];
};

struct Hitbox {
	//defines a hitbox
	Hitbox(aiVector3D min, aiVector3D max, HitboxFace left, HitboxFace right, HitboxFace top, HitboxFace bottom, HitboxFace front, HitboxFace back) :
		min(min), max(max), left(left), right(right), top(top), bottom(bottom), front(front), back(back) {};
	Hitbox(aiVector3D min, aiVector3D max) : min(min), max(max) {

		left = HitboxFace(HitboxVertex(min.x, min.y, min.z),
			HitboxVertex(min.x, min.y, max.z),
			HitboxVertex(min.x, max.y, max.z),
			HitboxVertex(min.x, max.y, min.z));

		right = HitboxFace(HitboxVertex(max.x, min.y, min.z),
			HitboxVertex(max.x, min.y, max.z),
			HitboxVertex(max.x, max.y, max.z),
			HitboxVertex(max.x, max.y, min.z));

		bottom = HitboxFace(HitboxVertex(min.x, min.y, min.z),
			HitboxVertex(max.x, min.y, min.z),
			HitboxVertex(max.x, min.y, max.z),
			HitboxVertex(min.x, min.y, max.z));

		top = HitboxFace(HitboxVertex(min.x, max.y, min.z),
			HitboxVertex(max.x, max.y, min.z),
			HitboxVertex(max.x, max.y, max.z),
			HitboxVertex(min.x, max.y, max.z));

		back = HitboxFace(HitboxVertex(min.x, min.y, min.z),
			HitboxVertex(max.x, min.y, min.z),
			HitboxVertex(max.x, max.y, min.z),
			HitboxVertex(min.x, max.y, min.z));

		front = HitboxFace(HitboxVertex(min.x, min.y, max.z),
			HitboxVertex(max.x, min.y, max.z),
			HitboxVertex(max.x, max.y, max.z),
			HitboxVertex(min.x, max.y, max.z));
	}

	aiVector3D min;
	aiVector3D max;

	HitboxFace left;
	HitboxFace right;
	HitboxFace top;
	HitboxFace bottom;
	HitboxFace front;
	HitboxFace back;
};

bool bboxIntersection(Hitbox a, Hitbox b);

bool mouseBboxIntersection(int x, int y, Hitbox h);