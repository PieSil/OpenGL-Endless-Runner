#pragma once
#include <GL\glut.h>
#include <string>

//define constants here

//assimp items id
static const int FAIRY_ID = 0;
static const int LWINGS_ID = 1;
static const int RWINGS_ID = 2;
static const int TEST_SPHERE_ID = 3;
static const int GROUND_ID = 6;
static const int LBORDER_ID = 4;
static const int RBORDER_ID = 5;
static const int LINVISIBLE_WALL_ID = 7;
static const int RINVISIBLE_WALL_ID = 8;
static const int SPIKEBALL_ID = 9;
static const int POINT_SPHERE_ID = 10;
static const int POWER1_ID = 11;
static const int POWER2_ID = 12;
static const int POWER3_ID = 13;
static const int SHELF_GROUND_ID = 14;
static const int SHELF_LBORDER_ID = 15;
static const int SHELF_RBORDER_ID = 16;
static const int RUPEE_GREEN_ID = 17;
static const int RUPEE_RED_ID = 18;
static const int RUPEE_BLUE_ID = 19;
static const int RUPEE_YELLOW_ID = 20;
static const int RUPEE_PURPLE_ID = 21;
static const int SWORD_POWERUP_ID = 22;
static const int SWORD_PROJECTILE_ID = 23;
static const int HEART_ID = 24;
static const int ZELDALOGO_ID = 25;
static const int CROSS_ID = 26;
static const int WHITE_RECTAGLE_ID = 28;
static const int RED_RECTANGLE_ID = 27;
static const int GAME_MENU = 29;
static const int START_BUTTON = 30;


//collectible properties
static const int COL_SPEED = 10;

//player properties
static const float SHOOT_POWER_DURATION = 10; //in seconds
static const float PROJECTILE_INTERVAL = .2; //in seconds
static const float FLIGHT_DURATION = 10; //in seconds
static const float PROJECTILE_SPEED = 50;
static const float INVICIBILITY_DURATION = 2; //in seconds
static const float INVICIBLE_DISPLAY_INTERVAL = .2; //in seconds

//model properties
static const double FAIRY_WING_SPEED = 80;
static const double MODEL_ROTATION_SPEED = 40;

//other settings
static const double FOV = 45.;
static void* FONT = GLUT_BITMAP_HELVETICA_18;
static const int FONT_HEIGHT = 18;
static const int INITIAL_GAME_SPEED = 10;
static const int INITIAL_WIDTH = 900;
static const int INITIAL_HEIGHT = 600;

//directories
static const std::string SCORE_DIR = "scores";
static const std::string SCORE_FILENAME = "scores.bin";

//UI properties
static const int UI_BAR_LENGTH = 200; //in pixels

//printable string
static const std::string TOP5_STRING = "TOP 5 SCORES: ";
static const std::string YOUR_SCORE_STRING = "YOUR SCORE: ";
static const std::string DEFAULT_STRING = "---: ---";

//audio files paths
static const std::string SUBWAY_BACK = "audio\\background-subway.mp3";
static const std::string RUPEE_SOUND = "audio\\rupee-sound.mp3";
static const std::string SWORD_SOUND = "audio\\magic-sword.wav";
static const std::string DAMAGE_SOUND = "audio\\hurt-sound.mp3";
static const std::string HEART_SOUND = "audio\\heart-sound.mp3";
static const std::string SHOOT_SOUND = "audio\\knife-sound.mp3";
static const std::string POP_SOUND = "audio\\pop-sound.mp3";