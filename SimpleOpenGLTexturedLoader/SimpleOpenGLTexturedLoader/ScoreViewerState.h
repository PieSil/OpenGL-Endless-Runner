#pragma once
#include "GameState.h"
class ScoreViewerState :
    public GameState {
public:
    ScoreViewerState(GameLogic* game);
    void handleInput(unsigned char key, int x, int y) override;
    void display() override;
private:
    std::vector<std::pair<std::string, int>> scores;
    std::vector<ShapeObject> scoreBackgrounds;
};

