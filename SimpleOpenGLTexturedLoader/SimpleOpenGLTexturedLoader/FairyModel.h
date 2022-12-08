#pragma once
#include "Model.h"

class FairyModel :
    public Model
{
public:
    explicit FairyModel(float wingsAngle = 0);
    void display(float x, float y, float z) override;
    void animate() override;

protected:
    float wingsAngle;
    float wingSpeed;
    bool wingsDown;
};

