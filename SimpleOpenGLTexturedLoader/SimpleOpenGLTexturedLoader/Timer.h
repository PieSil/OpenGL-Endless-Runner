#pragma once
#include <memory>
#include <windows.h>
#include <iostream>
#include <chrono>
#include "sysinfoapi.h"

//Timer class, needed to update game independently from framerate (FPS)

class Timer {
public:

	~Timer() {}; //dest

	static Timer* getTimer();

	int getElapsed() {
		//return elapsedTime.count() * 1000;
		return (int)std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count() * 1000;
	};


	void updateElapsed();

private:

	explicit Timer(); //private constructor, enables Singleton pattern, cannot have more than one instance of Timer at a time
	//double elapsedTime;
	//double totalTime;
	static std::shared_ptr<Timer> timerInstance;
	double PCFrequency = 0.0;
	__int64 CounterStart = 0;
	//std::chrono::system_clock clock;
	//std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> totalTime;
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> totalTime;
	//std::chrono::steady_clock totalTime;
	std::chrono::duration<double, std::nano> elapsedTime;
};

