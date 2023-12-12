#pragma once
#include "collidable.h"

class Ball : public collidable
{
    void collisionAction() override;

public:
    Ball(point r_uprleft, int r_radius, game* r_pGame);

private:
    int radius;
};

