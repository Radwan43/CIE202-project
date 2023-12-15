#include "ball.h"


Ball::Ball(point r_uprleft, int r_radius, game* r_pGame) :
    collidable(r_uprleft, 2 * r_radius, 2 * r_radius, r_pGame, "circle"),
    radius(r_radius)
{
    thetta = PI/2;

    speed = 2;
    std::cout << std::endl << cos(thetta) << " " << sin(thetta)<<std::endl;

    moving = 0;
}

void Ball::set_motion(bool moving) {
    this->moving = moving;
}

void Ball::setTrajectory(double thetta) {
    this->thetta = thetta;

}

void Ball::setSpeed(double speed) {
    this->speed = speed;
}

void Ball::moveBall() {

    bool shouldBreak = 0;
    while (moving = 1) {
        char kp;
        window* pWin = pGame->getWind();

        double xt = 0, yt = 0;
        for (int i = 0; i < 10; i++) {
            pWin->SetBrush(config.bkGrndColor);
            pWin->SetPen(config.bkGrndColor, 1);
            pWin->DrawCircle(uprLft.x + radius, uprLft.y + radius, radius);
            xt += speed*cos(thetta);
            yt += speed*sin(thetta);
            if (abs(xt) >= 1) {
                this->uprLft.x += xt;
                xt -= int(xt);
            };
            if (abs(yt) >= 1) {
                this->uprLft.y -= yt;
                yt -= int(yt);
            };

            for (int row = 0; row < pGame->getGrid()->getrows(); row++) {
                for (int col = 0; col < pGame->getGrid()->getcols(); col++) {
                    if (pGame->getGrid()->getMatrix()[row][col]) {
                        point CollisionPoint = CheckCollision(this, pGame->getGrid()->getMatrix()[row][col]);
                        if (CollisionPoint.x != 0 || CollisionPoint.y != 0) {
                            pGame->getGrid()->getMatrix()[row][col]->collisionAction();
                            shouldBreak = 1;
                            break;
                        }
                    }
                }
                if (shouldBreak) break;
            }


                

                draw();
                if (shouldBreak) break;
                std::this_thread::sleep_for(std::chrono::nanoseconds(5000));




        }
        if (shouldBreak) break;
    }
    if (shouldBreak) this->collisionAction();
}




void Ball::collisionAction() {
    this->setTrajectory(-1*this->thetta);
    this->moveBall();
    // Implement collision action for normalpaddle
    // Implement collision action for walls
    // Implement collision action with bricks
    // Implement collision action with bottom (respawn ball attatched to paddle, life--)
}


