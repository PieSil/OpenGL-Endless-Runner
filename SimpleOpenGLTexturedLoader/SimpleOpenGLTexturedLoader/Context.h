#pragma once
#include <memory>
//A class containing useful informations about the context of the application, e.g. current window resolution, game difficulty and other settings

class Context {
public:

	~Context() {}; //dest

	static Context* getContext();

	void setWidthHeight(float w, float h) {
		width = w;
		height = h;
		aspectRatio = w / h;
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
		gameSpeed += value;
	}

	float getGameSpeed() {
		return gameSpeed;
	}


private:

	explicit Context(); //private constructor, enables Singleton pattern, cannot have more than one instance of Timer at a time
	static std::shared_ptr<Context> contextInstance;
	float width;
	float height;
	float aspectRatio;
	float scaleFactor;
	int score;
	float gameSpeed;
	double fieldOfView;
};

