#pragma once
#include "GameState.h"
class MenuState :
    public GameState
{
public:
    void display();
    void handleInput(unsigned char key, int x, int y);
    explicit MenuState(GameLogic* pointer, bool persp = FALSE);
    void mouseMotion(int x, int y) override;
    void mouse(int button, int state, int x, int y) override;

private:
    ShapeObject menu;
    ShapeObject startButton;
    GameLogic* game;
};
