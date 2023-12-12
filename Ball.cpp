#include "ball.h"

Ball::Ball(point r_uprleft, int r_radius, game* r_pGame) :
    collidable(r_uprleft, 2 * r_radius, 2 * r_radius, r_pGame, "circle"),
    radius(r_radius)
{
}


void Ball::collisionAction() {
    // Implement collision action for normalpaddle
}


