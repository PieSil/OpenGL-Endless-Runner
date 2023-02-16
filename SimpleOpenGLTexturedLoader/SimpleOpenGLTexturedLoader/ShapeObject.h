#pragma once
#include "GameObject.h"
#include "Model.h"
#include <memory>
#include<GL/glut.h>

//A GameObkect which is also associated to a model (be it an OpenGL model, like a solid cube, or a model imported through assimp)
//this class and its parent class (GameObject) may be fused into a single class

class ShapeObject :
    public GameObject {
public:
    explicit ShapeObject(float x, float y, float z, std::shared_ptr<Model> _shape, aiVector3D scale = aiVector3D(1,1,1), float speed = 0.);
    explicit ShapeObject();

    virtual void display() override;
    virtual void update() override;
    void getHitbox(struct aiVector3D* min, struct aiVector3D* max);
    void setModel(std::shared_ptr<Model> newShape);

protected:
    std::shared_ptr<Model> shape;
};

