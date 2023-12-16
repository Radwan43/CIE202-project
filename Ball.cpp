#include "ball.h"


Ball::Ball(point r_uprleft, int r_radius, game* r_pGame) :
    collidable(r_uprleft, 2 * r_radius, 2 * r_radius, r_pGame, "circle"),
    radius(r_radius)
{
    thetta = PI/4;

    speed = 10;

    step_x = speed * cos(thetta);
    
    step_y = -speed * sin(thetta);

    moving = 0;
}

void Ball::set_motion(bool moving) {
    this->moving = moving;
}

void Ball::setTrajectory(double thetta) {
    this->thetta = thetta;

    step_x = speed * cos(thetta);
    step_y = -speed * sin(thetta);
}

void Ball::setSpeed(double speed) {
    step_x *= speed / this->speed;
    step_y *= speed / this->speed;
    this->speed = speed;
}

void Ball::moveBall() {

    while (moving = 1) {

        int x_stepsMoved, Y_stepsMoved;
        x_stepsMoved = 0;
        Y_stepsMoved = 0;
        for (int i = 0; i < abs(step_x) && i < abs(step_y); i++) {
            if (x_stepsMoved != abs(step_x)) {
                uprLft.x += step_x / abs(step_x);
                x_stepsMoved++;
            }
            if (Y_stepsMoved != abs(step_y)) {
                uprLft.y += step_y / abs(step_y);
                Y_stepsMoved++;
            }



            for (int row = 0; row < pGame->getGrid()->getrows(); row++) {
                for (int col = 0; col < pGame->getGrid()->getcols(); col++) {
                    if (pGame->getGrid()->getMatrix()[row][col]) {
                        point CollisionPoint = CheckCollision(this, pGame->getGrid()->getMatrix()[row][col]);
                        if (CollisionPoint.x != 0 || CollisionPoint.y != 0) {
                            collidedWithBrick = true;
                            lastcollidedBrick = CollisionPoint;
                            this->collisionAction();
                            pGame->getGrid()->getMatrix()[row][col]->collisionAction();
                        }
                        CollisionPoint.x = 0;
                        CollisionPoint.y = 0;
                    }
                }
            }
            // Check collisions with walls
            if (uprLft.y <= 0) {
                collidedWithWallTop = true;
                this->collisionAction();
            }
            else if (uprLft.x <= 0) {
                collidedWithWallLeft = true;
                this->collisionAction();
            }
            else if (uprLft.x + radius >= pGame->getWind()->GetWidth()) {
                collidedWithWallRight = true;
                this->collisionAction();
            }
            else if (uprLft.y + radius >= pGame->getWind()->GetHeight()) {
                collidedWithWallBottom = true;
                this->collisionAction();
            }
            // Check collisions with paddle
            else if (CheckCollision(this, ptpaddle).x != 0 || CheckCollision(this, ptpaddle).y != 0) {
				collidedWithPaddle = true;
				this->collisionAction();
            }


        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        window* pWin = pGame->getWind();
        pWin->SetBrush(config.bkGrndColor);
        pWin->SetPen(config.bkGrndColor, 1);
        pWin->DrawCircle(uprLft.x + radius-step_x, uprLft.y + radius-step_y, radius);

        draw();
    }
}




// collisionAction() is called when a collision is detected, and it is responsible for the action that should be taken when a collision is detected
// normal paddle: change ball trajectory based on where it hit the paddle and the angle of incidence
//walls: change ball trajectory based on which wall it hit, theta reflected = theta incident
//bricks: change ball trajectory based on which brick it hit, theta reflected = theta incident
//if ball position is lower than paddle position, respawn ball attatched to paddle, life--
void Ball::collisionAction() {
    //Check collision with corners of ball and brick
    bool topLcol = false;
    bool topRcol = false;
    bool bottomLcol = false;
    bool bottomRcol = false;
    if (collidedWithBrick) {
        if ((lastcollidedBrick.x == uprLft.x) && (lastcollidedBrick.y == uprLft.y)) { topLcol = true; }
        else if ((lastcollidedBrick.x == (uprLft.x + radius)) && (lastcollidedBrick.y == (uprLft.y))) { topRcol = true; }
        else if ((lastcollidedBrick.x == (uprLft.x + radius)) && (lastcollidedBrick.y == (uprLft.y + radius))) { bottomRcol = true; }
        else if ((lastcollidedBrick.x == (uprLft.x)) && (lastcollidedBrick.y == (uprLft.y + radius))) { bottomLcol = true; }
    }

    //collision action with bricks and walls
    if (topLcol || topRcol || bottomLcol || bottomRcol) {
        thetta = PI + thetta;
        topLcol, topRcol, bottomLcol, bottomRcol = false;
    }
    else if (collidedWithBrick || collidedWithWallBottom || collidedWithWallLeft || collidedWithWallRight || collidedWithWallTop) {
        if (collidedWithWallLeft || collidedWithWallRight || is_collided(uprLft.x, lastcollidedBrick.x, uprLft.y, lastcollidedBrick.y, radius, 60, radius, 30)) {
			thetta = PI - thetta; // Reflect horizontally
			collidedWithWallRight, collidedWithWallLeft = false;
		}
        else if (collidedWithWallTop || is_collided(uprLft.y, lastcollidedBrick.y, uprLft.x, lastcollidedBrick.x, -30, -radius, 60, radius)) {
            thetta = -thetta; // Reflect vertically
            collidedWithWallTop = false;
        }
        else if (collidedWithWallBottom) { //destrust ball and respawn on paddle and decrement life by 1
            //life --
            delete this;
            //respawn ball on paddle
            Ball* newball = new Ball({ ptpaddle->getUpperLeft().x + ptpaddle->getWidth() / 2, ptpaddle->getUpperLeft().y - radius }, radius, pGame);
        }
    }

    //collision action with paddle
    if (collidedWithPaddle) {
        point relativeHitPoint;
        relativeHitPoint.x = uprLft.x - ptpaddle->getUpperLeft().x;
        relativeHitPoint.y = uprLft.y - ptpaddle->getUpperLeft().y;
        double normalizedHitPos = relativeHitPoint.x / ptpaddle->getWidth();
        double newTheta = PI / 2 + normalizedHitPos * maxAngle;
        thetta = newTheta;
        collidedWithPaddle = false;
    }
}


