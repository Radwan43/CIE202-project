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
                            this->collisionAction();
                            pGame->getGrid()->getMatrix()[row][col]->collisionAction();
                        }
                        CollisionPoint.x = 0;
                        CollisionPoint.y = 0;
                    }
                }
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




void Ball::collisionAction() {
    // Implement collision action for normalpaddle
    // Implement collision action for walls
    // Implement collision action with bricks
    // Implement collision action with bottom (respawn ball attatched to paddle, life--)
}


