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
		////return elapsedTime.count() * 1000;
		//double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsedTime).count();
		//std::cout << "Elapsed time: " << elapsed << " nanos\n";
		//double intElapsed = double(elapsed / 1000000);
		//std::cout << "Output elapsed: " << intElapsed << "\n";
		//return intElapsed;
		//std::cout << "Elapsed: " << elapsedTime / 1000 << " millis \n";

		//RETURNS ELAPSED TIME IN MILLISECONDS
		return elapsedTime/1000;

	}


	void updateElapsed();
	void start();
	void end();

private:

	explicit Timer(); //private constructor, enables Singleton pattern, cannot have more than one instance of Timer at a time
	//double elapsedTime;
	//double totalTime;
	static std::shared_ptr<Timer> timerInstance;
	//std::chrono::system_clock clock;
	//std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> totalTime;
	/*std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> currentTime;
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> totalTime;*/
	//std::chrono::steady_clock totalTime;
	/*std::chrono::duration<double, std::nano> elapsedTime;*/
	double elapsedTime;
	double totalTime;

};

