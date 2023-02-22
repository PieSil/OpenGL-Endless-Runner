#pragma once
#include <memory>
#include <iostream>
#include <chrono>
#include "GLutils.h"

//Timer class, needed to update game independently from framerate (FPS)

class Timer {
public:

	~Timer() {}; //dest

	static Timer* getTimer();

	double getElapsed() {
		//RETURNS ELAPSED TIME IN SECONDS
		return elapsedTime.count()/1000;

	}


	void updateElapsed();

private:

	explicit Timer(); //private constructor, enables Singleton pattern, cannot have more than one instance of Timer at a time
	static std::shared_ptr<Timer> timerInstance;

	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> currentTime;
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> totalTime;
	std::chrono::duration<double, std::milli> elapsedTime;

};

