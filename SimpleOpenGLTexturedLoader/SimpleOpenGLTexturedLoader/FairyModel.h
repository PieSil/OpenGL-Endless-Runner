#pragma once
#include "Model.h"

//An implementation of Model abstract class, display function renders a fairy

class FairyModel :
    public Model
{
public:
    explicit FairyModel(float wingsAngle = 0);
    void display(float x, float y, float z, aiVector3D scale = aiVector3D(1, 1, 1)) override;
    void animate() override;
    void getHitbox(struct aiVector3D* min, struct aiVector3D* max) override;
    void resetAnimation() override {
        wingsAngle = 0;
    }

protected:
    float wingsAngle;
    float wingSpeed;
    bool wingsDown;
};

