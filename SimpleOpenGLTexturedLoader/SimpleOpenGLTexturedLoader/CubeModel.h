#pragma once
#include "Model.h"
#include <GL/glut.h>

//An implementation of Model abstract class, display function renders a cube

class CubeModel :
    public Model {
public:

    explicit CubeModel(float _size);

    void display(float x, float y, float z, aiVector3D scale = aiVector3D(1, 1, 1)) override;
    void getHitbox(struct aiVector3D* min, struct aiVector3D* max) override;

protected:
    float size;
};
