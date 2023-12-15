#pragma once
#include "drawable.h"

///////////////////////////////////////   collidable classes   /////////////////////////////////
// Base class for all collidable objects (objects that may collide with other objects)
class collidable : public drawable
{
public:
    collidable(point r_uprleft, int r_width, int r_height, game* r_pGame);
    collidable(point r_uprleft, int r_width, int r_height, game* r_pGame, const string& shapeType);
    static point CheckCollision(collidable* object1, collidable* object2);
    
    static bool is_collided(int u1, int u2, int v1, int v2, int width1, int width2, int height1, int height2);
    static bool is_onLine(int u1, int u2, int distance2);
    static bool is_inRange(int u1, int u2, int distance1, int distance2);

    virtual void collisionAction() = 0;    //action that should be performed upon collision
};
