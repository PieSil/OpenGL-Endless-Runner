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

	double getElapsed() {
		return elTime.count() * 1000;
		//return std::chrono::duration_cast<std::chrono::seconds>(elTime).count();
		//return clock.duration().count();
	};

	/*double getElapsedSeconds() {
		return elapsedTime/1000000;
	}*/

	void updateElapsed();


	//disable copy and assignment
	//Timer(const Timer&) = delete;
	//Timer& operator=(const Timer&) = delete;
private:

	//void StartCounter() {
	//	//stole from the internet, initializes timer
	//	LARGE_INTEGER li;
	//	if (!QueryPerformanceFrequency(&li))
	//		std::cout << "QueryPerformanceFrequency failed!\n";

	//	PCFrequency = double(li.QuadPart) / 1000.0;

	//	QueryPerformanceCounter(&li);
	//	CounterStart = li.QuadPart;
	//}

	//double GetCounter() {
	//	//stole from the internet, return time IN SECONDS (probably)
	//	LARGE_INTEGER li;
	//	QueryPerformanceCounter(&li);
	//	return double(li.QuadPart - CounterStart) / PCFrequency;
	//}

	explicit Timer(); //private constructor, enable Singleton pattern, cannot have more than one instance of timer at a time
	double elapsedTime;
	double totalTime;
	static std::shared_ptr<Timer> timerInstance;
	double PCFrequency = 0.0;
	__int64 CounterStart = 0;
	std::chrono::system_clock clock;
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> totTime;
	std::chrono::duration<double> elTime;
};

