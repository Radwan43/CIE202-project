#pragma once
#include "collidable.h"
#include <chrono>
#include <thread>
#include "gameConfig.h"
#include "game.h"
#include <iostream> 

class Ball : public collidable
{
    void collisionAction() override;


public:
    Ball(point r_uprleft, int r_radius, game* r_pGame);

private:
    const double PI = 3.14159265359;
    int radius;
    double thetta;
    int speed;
    bool moving, attatched;
    double xt, yt;

public:
    bool isMoving();
    bool isAttatched();
    void set_motion(bool moving);
    void setTrajectory(double thetta);
    void setSpeed(double speed);
    void setAttatched(bool attatched);
    void moveBall();
    void MoveAttatchedBall();
    point getUprleft();
    int getRadius();

};
