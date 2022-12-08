#pragma once
#include "GameObject.h"
#include "Model.h"
#include <memory>
#include<GL/glut.h>
class ShapeObject :
    public GameObject {
public:
    explicit ShapeObject(float x, float y, float z, std::shared_ptr<Model> _shape, float speed = 0);
    void display() override;
    void update() override;

protected:
    std::shared_ptr<Model> shape;
};

