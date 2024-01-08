#include "GameTimer.h"
#include <sstream>

GameTimer::GameTimer() : running(false) {}

void GameTimer::start() {
    startTime = std::chrono::steady_clock::now();
    running = true;
}


bool GameTimer::isRunning() {
    return running;
}


void GameTimer::update() {
    // Implementation remains the same as in the previous version
}

void GameTimer::stop() {
    running = false;
}

std::string GameTimer::getElapsedTimeString() const {
    if (running) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        std::stringstream ss;
        ss << elapsedTime;
        return ss.str();
    }
    else {
        return "0 seconds";
    }
}
