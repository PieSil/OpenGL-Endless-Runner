#include "Timer.h"

std::shared_ptr<Timer> Timer::timerInstance(nullptr);

Timer::Timer() {
    currentTime = std::chrono::steady_clock::now();
    totalTime = std::chrono::steady_clock::now();
    elapsedTime = totalTime - totalTime; //init elapsedTime to 0
    //elapsedTime = 0;
    //totalTime = 0;
}

Timer* Timer::getTimer() {
    //singleton pattern, if timerInstance does not exist create one and return pointer to timerInstance
    //otherwise only return pointer
    if (!timerInstance) {
        timerInstance.reset(new Timer());
    }
    return timerInstance.get();
}

void Timer::updateElapsed() {
    //updates elapsed time since last call, stores currentTime into totalTime for future computations
    //std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> currentTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    elapsedTime = currentTime - totalTime;
    totalTime = currentTime;
    /*double currentTime = glutGet(GLUT_ELAPSED_TIME);
    elapsedTime = currentTime - totalTime;
    totalTime = currentTime;*/
    //std::cout << "Elapsed time: " << elapsedTime << " millis\n";
    //std::cout << "Output elapsed: " << elapsedTime / 1000 << "\n";
}

void Timer::start() {
 /*   totalTime = std::chrono::steady_clock::now();*/
}

void Timer::end() {
    /*auto currentTime = std::chrono::steady_clock::now();
    elapsedTime = currentTime - totalTime;*/
}
