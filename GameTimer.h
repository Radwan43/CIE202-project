#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <iostream>
#include <chrono>
#include <thread>

class GameTimer {
public:
    GameTimer();

    void start();
    void update(); // Update the timer (call this in your game loop)
    void stop();

    std::string getElapsedTimeString() const; // Get the elapsed time as a string

private:
    std::chrono::steady_clock::time_point startTime;
    bool running;
};

#endif // GAMETIMER_H
