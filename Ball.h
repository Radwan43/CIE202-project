#pragma once
#include "collidable.h"
#include <chrono>
#include <thread>
#include "gameConfig.h"
#include "game.h"
#include "paddle.h"
#include "Bricks.h"
#include <iostream> 

#define MAX_ANGLE 0.785f //45 degrees in radians

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
    bool moving;
    bool collidedWithPaddle = false;
    bool collidedWithBrick = false;
    bool collidedWithWallTop = false;
    bool collidedWithWallBottom = false;
    bool collidedWithWallLeft = false;
    bool collidedWithWallRight = false;
    paddle* ptpaddle;
    float maxAngle = MAX_ANGLE;
    point lastcollidedBrick;
public:
    void set_motion(bool moving);
    void setTrajectory(double thetta);
    void setSpeed(double speed);
    void moveBall();
};
