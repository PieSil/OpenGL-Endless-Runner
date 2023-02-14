#pragma once
#include "Model.h"
#include <GL/glut.h>

//An implementation of Model abstract class, display function renders a sphere

class SphereModel :
    public Model {
public:

    explicit SphereModel(float radius, int slices = 32, int stacks = 32);

    void display(float x, float y, float z, bool ortho = false) override;
    void getHitbox(struct aiVector3D* min, struct aiVector3D* max) override;

protected:
    float radius;
    int slices;
    int stack;
};
