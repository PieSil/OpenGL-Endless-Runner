#include "Timer.h"

std::shared_ptr<Timer> Timer::timerInstance(nullptr);

Timer::Timer() {
    //StartCounter();
    //elapsedTime = 0;
    totTime = std::chrono::steady_clock::now();
    elTime = totTime - totTime; //init elapsedTime to 0
    //clock.tick();
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
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> currentTime = std::chrono::steady_clock::now();
    elTime = currentTime - totTime;
    totTime = currentTime;
}
