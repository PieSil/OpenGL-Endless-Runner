#pragma once
#include <memory>
//A class containing useful informations about the context of the application, e.g. current window resolution

class Context {
public:

	~Context() {}; //dest

	static Context* getContext();

	void setWidthHeight(float w, float h) {
		width = w;
		height = h;
		aspectRatio = w / h;
	}

	void setScaleFactor(float sf) {
		scaleFactor = sf;
	}

	float getScaleFactor() {
		return scaleFactor;
	}

private:

	explicit Context(); //private constructor, enables Singleton pattern, cannot have more than one instance of Timer at a time
	static std::shared_ptr<Context> contextInstance;
	float width;
	float height;
	float aspectRatio;
	float scaleFactor;
};

