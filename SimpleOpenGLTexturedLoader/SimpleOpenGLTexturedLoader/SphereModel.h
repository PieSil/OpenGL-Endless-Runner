#pragma once
#include "Model.h"
#include <GL/glut.h>
class SphereModel :
    public Model {
public:

    explicit SphereModel(float radius, int slices = 32, int stacks = 32);

    void display(float x, float y, float z) override;

protected:
    float radius;
    int slices;
    int stack;
};
