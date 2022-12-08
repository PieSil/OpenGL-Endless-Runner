#pragma once
#include "Model.h"
#include <GL/glut.h>
class CubeModel :
    public Model {
public:

    explicit CubeModel(float _size);

    void display(float x, float y, float z) override;

protected:
    float size;
};
