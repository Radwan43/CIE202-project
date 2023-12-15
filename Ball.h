#pragma once
#include "collidable.h"
#include <chrono>
#include <thread>
#include "gameConfig.h"
#include "game.h"

class Ball : public collidable
{
    void collisionAction() override;


public:
    Ball(point r_uprleft, int r_radius, game* r_pGame);

private:
    const double PI = 3.14159265359;
    int radius;
    double thetta;
    int step_x, step_y;
    int speed;
    bool moving;
public:
    void set_motion(bool moving);
    void setTrajectory(double thetta);
    void setSpeed(double speed);
    void moveBall();
};
