#pragma once
#include "Model.h"

//An implementation of Model abstract class, display function renders a fairy

class FairyModel :
    public Model
{
public:
    explicit FairyModel(float wingsAngle = 0);
    void display(float x, float y, float z, bool ortho = false) override;
    void animate() override;
    void getHitbox(struct aiVector3D* min, struct aiVector3D* max) override;

protected:
    float wingsAngle;
    float wingSpeed;
    bool wingsDown;
};

