#pragma once
#include "collidable.h"
#include <chrono>
#include <thread>
#include "gameConfig.h"
#include "game.h"
#include "paddle.h"
#include "Bricks.h"
#include <iostream> 

class brick;
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
    bool collidedWithPaddle = false;
    bool collidedWithBrick = false;
    bool collidedWithWallTop = false;
    bool collidedWithWallBottom = false;
    bool collidedWithWallLeft = false;
    bool collidedWithWallRight = false;
    paddle* ptpaddle;
    brick* lastcollidedBrick;
    bool moving, attatched;
    double xt, yt;

    int lifes = 3;
    bool isFireBall;

public:
    double getPI() const;
    bool isMoving();
    bool isAttatched();
    void set_motion(bool moving);
    void setTrajectory(double thetta);
    void setSpeed(double speed);
    void setAttatched(bool attatched);
    int getLife();
    void setLife(int life);
    void moveBall();
    void MoveAttatchedBall();
    point getUprleft();
    int getRadius();

    bool getIsFireBall();

    void setIsFireBall(bool change);

};