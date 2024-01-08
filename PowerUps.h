#pragma once
#include "collidable.h"
#include <chrono>
#include <thread>
#include "gameConfig.h"
#include "game.h"
#include "paddle.h"
#include "Bricks.h"
#include <iostream> 


class game;
class PowerUps : public collidable
{
    void collisionAction() override;


public:
    PowerUps(point r_uprleft, game* r_pGame);

private:
   
    int speed;
    bool moving ;
    double xt, yt;

public:
    bool isMoving();
    void set_motion(bool moving);
    void setSpeed(double speed);
    void movePowerUp();
    point getUprleft();
};
