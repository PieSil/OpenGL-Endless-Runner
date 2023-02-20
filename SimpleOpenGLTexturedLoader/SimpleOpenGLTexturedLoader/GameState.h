#pragma once
#include <memory>
#include "GameLogic.h"
#include "ModelRepository.h"
#include "AudioPlayer.h"
#include "Timer.h";

//abstract class, represents a state of the game, like menu, playing state, pause, etc. 
//multiple states can be active at once thanks to a stack structure (see GameLogic class)

class GameState {
   
public:
    explicit GameState(GameLogic* game, bool persp = false, std::string backgroundMusicPath = FAIRY_BACKGROUND);

    virtual ~GameState() {
    };

    virtual void update();
    virtual void handleInput(unsigned char key, int x, int y) = 0;
    virtual void display();
    virtual void handleInputUp(unsigned char key, int x, int y) {};
    virtual void mouseMotion(int x, int y) {};
    virtual void activeMouseMotion(int x, int y) {};
    virtual void mouse(int button, int state, int x, int y) {};
    virtual void handleSpecialInput(int key, int x, int y) {};
    virtual void handleSpecialInputUp(int key, int x, int y) {};
    void setPerspective(bool setModelView = true);
    void setCamera();
    void drawBackground(bool persp = false);

    void setPerspMode(bool usePersp, bool autoSetPersp = true, bool autoSetCamera = true) { 
        //if usePersp == true switches to perspective mode, otherwise switches to orthographic mode
        //if autoSetPersp == true also modifies the projection matrix accordingly using glPerspective/glOrtho THIS WILL AUTOMATICALLY SWITCH TO THE MODELVIEW MATRIX AFTER SETTING THE PERSPECTIVE MODE
        //if autoSetCamera == true also modifies the location of the camera according to new perspective <--THIS WILL ONLY BE CONSIDERED IF autoSetPersp IS ALSO "true"
        persp = usePersp;
        if (autoSetPersp) {
            setPerspective();
            if (autoSetCamera) {
                setCamera();
            }
        }
    }

    virtual void playBackground() {
     
        if (AudioPlayer::setBackground(backgroundMusicPath) || !AudioPlayer::isBackgroundActive()) {
            AudioPlayer::dropBackground();
            AudioPlayer::playBackground();
        }
    }

    void dropBackground() {
        AudioPlayer::dropBackground();
    }

    void incrCameraAngle(float value) {

        //value *= Timer::getTimer()->getElapsed();

        cameraAngle += value;
        if (cameraAngle >= BASE_CAMERA_ANGLE + 30.f) {
            cameraAngle = BASE_CAMERA_ANGLE+30.f;
        }
        else if (cameraAngle <= BASE_CAMERA_ANGLE-30.f) {
            cameraAngle = BASE_CAMERA_ANGLE-30.f;
        }

    }

    void resetCameraAngle() {
        cameraAngle = BASE_CAMERA_ANGLE;
    }

protected:
    //GameLogic* game;
    GameLogic* game; //a pointer to the GameLogic object, this is necessary in order to push/pop/set a state from within another state 
    std::vector<std::shared_ptr<GameObject>> objects; //a list of (pointers to) objects that need to be rendered
    std::string backgroundMusicPath;
    float cameraAngle;
    bool persp;
 
};

