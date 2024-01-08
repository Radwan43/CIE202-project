#include "GameTimer.h"
#include <sstream>
#include <chrono>

GameTimer::GameTimer() : running(false), totalElapsedTime(0) {}

void GameTimer::start() {
    if (!running) {
        startTime = std::chrono::steady_clock::now();
        running = true;
    }
}


bool GameTimer::isRunning() {
    return running;
}

void GameTimer::pause() {
    if (running) {
        auto currentTime = std::chrono::steady_clock::now();
        totalElapsedTime += std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        running = false;
    }
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
        auto elapsedTime = totalElapsedTime + std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        std::stringstream ss;
        ss << elapsedTime << " seconds";
        return ss.str();
    }
    else {
        std::stringstream ss;
        ss << totalElapsedTime << " seconds";
        return ss.str();
    }
}
