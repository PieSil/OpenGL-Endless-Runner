#pragma once
#include <memory>
#include <string>
#include "Const.h"
//A class containing useful informations about the context of the application, e.g. current window resolution, game difficulty and other settings

class Context {
public:

	~Context() {}; //dest

	static Context* getContext();

	void setWidthHeight(float w, float h) {
		width = w;
		height = h;
		aspectRatio = w / h;
		orthoScaleFactorX = (float)INITIAL_WIDTH / width;
		orthoScaleFactorY = (float)INITIAL_HEIGHT / height;
	}

	float getWidth() {
		return width;
	}

	float getHeight() {
		return height;
	}

	void setScaleFactor(float sf) {
		scaleFactor = sf;
	}

	float getScaleFactor() {
		return scaleFactor;
	}

	
	float getAspectRatio() {
		return aspectRatio;
	}

	double getFieldOfView() {
		return fieldOfView;
	}

	void incrScore(int value) {
		score += value;
		if (score < 0) {
			score = 0;
		}
	}

	int getScore() {
		return score;
	}

	void resetScore() {
		score = 0;
	}

	void setGameSpeed(float value) {
		gameSpeed = value;
	}

	void incrGameSpeed(float value) {
		if (gameSpeed < MAX_SPEED)
			gameSpeed += value;
	}

	float getGameSpeed() {
		return gameSpeed;
	}

	void concatCharToPlayerName(char c) {
		playerName += c;
	}

	void clearPlayerName() {
		playerName = "";
	}

	std::string getPlayerName() {
		return playerName;
	}

	void deletePlayerNameChar() {
		if (!playerName.empty())
			playerName.erase(playerName.size() - 1);
	}

	float  getRelativeWindowX(float fraction, float offset = 0.f) {
		return (width / 2.f) - (width * fraction) - offset;
	}

	float  getRelativeWindowY(float fraction, float offset = 0.f) {
		return (height / 2.f) - (height * fraction) - offset;
	}

	float getScaleForTarget(float targetValue, float actualValue) {
		return actualValue/targetValue;
	}

	float getOrthoScaleX() {
		return orthoScaleFactorX;
	}

	float getOrthoScaleY() {
		return orthoScaleFactorY;
	}

private:

	explicit Context(); //private constructor, enables Singleton pattern, cannot have more than one instance of Timer at a time
	static std::shared_ptr<Context> contextInstance;
	float width;
	float height;
	float aspectRatio;
	float scaleFactor;
	float orthoScaleFactorX;
	float orthoScaleFactorY;
	int score;
	float gameSpeed;
	double fieldOfView;
	std::string playerName;
};

