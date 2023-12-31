#include "ball.h"


Ball::Ball(point r_uprleft, int r_radius, game* r_pGame) :
    collidable({ r_uprleft.x - r_radius ,r_uprleft.y }, 2 * r_radius, 2 * r_radius, r_pGame, "circle"),
    radius(r_radius)
{
    thetta = PI/2;


    speed = 4;
    xt = 0;
    yt = 0;

    ptpaddle = pGame->getPaddle();
    lastcollidedBrick = nullptr;
    isFireBall = false;
    moving = 0;
    attatched = 1;
}

double Ball::getPI() const {
    return this->PI;
}


bool Ball::isMoving() {
    return this->moving;
}

bool Ball::isAttatched() {
    return this->attatched;
}

point Ball::getUprleft() {
    return uprLft;
}

int Ball::getRadius() {
    return radius;
}

void Ball::setIsFireBall(bool change)
{
    isFireBall = change;
}

bool Ball::getIsFireBall() {
    return isFireBall;
}


void Ball::set_motion(bool moving) {
    this->moving = moving;
}

void Ball::setAttatched(bool attatched) {
    this->attatched = attatched;
}

void Ball::setTrajectory(double thetta) {
    this->thetta = thetta;

}

void Ball::setSpeed(double speed) {
    this->speed = speed;
}


void Ball::moveBall() {

    if (moving == 1&& pGame->getMode()!=MODE_PAUSE) {
        window* pWin = pGame->getWind();
        point CollisionPoint;
        int br = 0;
        pWin->SetBrush(config.bkGrndColor);
        pWin->SetPen(config.bkGrndColor, 1);
        pWin->DrawCircle(uprLft.x + radius, uprLft.y + radius, radius);
        xt += speed * cos(thetta);
        yt += speed * sin(thetta);


        while (br != 1 && ((abs(yt) > 1) || (abs(xt) > 1))) {


            if (abs(xt) >= 1) {
                this->uprLft.x += xt/ abs(xt);
                xt -= xt / abs(xt);
            };
            if (abs(yt) >= 1) {
                this->uprLft.y -= yt/abs(yt);
                yt -= yt / abs(yt);
            };

            for (int row = 0; row < pGame->getGrid()->getrows(); row++) {
                for (int col = 0; col < pGame->getGrid()->getcols(); col++) {
                    if (pGame->getGrid()->getMatrix()[row][col]) {
                        CollisionPoint = CheckCollision(this, pGame->getGrid()->getMatrix()[row][col]);
                        if (CollisionPoint.x != 0 || CollisionPoint.y != 0) {
                            collidedWithBrick = true;
                            lastcollidedBrick = pGame->getGrid()->getMatrix()[row][col];

                            cout <<endl<< "collided with brick" << endl;

                            cout << endl << "ball x: " << this->uprLft.x;
                            cout << endl << "ball y: " << this->uprLft.y;
                            cout << endl << "brick x: " << pGame->getGrid()->getMatrix()[row][col]->getUprleft().x;
                            cout << endl << "brick y: " << pGame->getGrid()->getMatrix()[row][col]->getUprleft().y;
                            this->collisionAction();
                            pGame->getGrid()->getMatrix()[row][col]->collisionAction();


                            br = 1;
                            break;
                        }
                    }
                }
                if (br == 1) break;
            }

            // Check collisions with paddle
            if (br == 0) {
                if ((CheckCollision(this, ptpaddle).x != 0)) {
                    collidedWithPaddle = true;
                    cout << "collided with paddle";
                    this->collisionAction();
                }
                // Check collisions with walls
                else if (uprLft.y <= config.toolBarHeight) {
                    collidedWithWallTop = true;
                    this->collisionAction();
                }
                else if (uprLft.x <= 0) {
                    collidedWithWallLeft = true;
                    this->collisionAction();
                }
                else if (uprLft.x + this->width >= config.windWidth) {
                    collidedWithWallRight = true;
                    this->collisionAction();
                }
                else if (uprLft.y + this->height + config.statusBarHeight >= config.windHeight) {
                    collidedWithWallBottom = true;
                    this->collisionAction();
                }

            }

        };

        draw();
        std::this_thread::sleep_for(std::chrono::nanoseconds(50000));


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
    point brickuprlft = { 0,0 };
    if (lastcollidedBrick) {
        brickuprlft = lastcollidedBrick->getUprleft();
    }

    //corner collision
    if (collidedWithBrick) {
        if ((brickuprlft.x == uprLft.x) && (brickuprlft.y == uprLft.y)) { topLcol = true; }
        else if ((brickuprlft.x == (uprLft.x + radius)) && (brickuprlft.y == (uprLft.y))) { topRcol = true; }
        else if ((brickuprlft.x == (uprLft.x + radius)) && (brickuprlft.y == (uprLft.y + radius))) { bottomRcol = true; }
        else if ((brickuprlft.x == (uprLft.x)) && (brickuprlft.y == (uprLft.y + radius))) { bottomLcol = true; }
    };

    //collision action with bricks and walls
    if (topLcol || topRcol || bottomLcol || bottomRcol) {
        thetta = PI + thetta;
        topLcol = topRcol = bottomLcol = bottomRcol = false;
        collidedWithBrick = false;
    }
    else if (collidedWithBrick || collidedWithWallBottom || collidedWithWallLeft || collidedWithWallRight || collidedWithWallTop) {
        if (collidedWithWallLeft || collidedWithWallRight || lastcollidedBrick != nullptr && (is_collided(uprLft.x, brickuprlft.x, uprLft.y, brickuprlft.y, this->width, config.brickWidth, this->height, config.brickHeight))) {
            if (!isFireBall || collidedWithWallRight || collidedWithWallLeft) {

                thetta = PI - thetta; // Reflect horizontally

                if (collidedWithWallRight || uprLft.x + this->width == brickuprlft.x) {
                    uprLft.x--;
                }
                else {
                    uprLft.x++;
                };
            };
            collidedWithWallRight = false;
            collidedWithWallLeft = false;
            collidedWithBrick = false;
            lastcollidedBrick = nullptr;

        }
        else if (collidedWithWallTop) {
            thetta = -thetta; // Reflect vertically
            collidedWithWallTop = false;
            uprLft.y++;
        }
        else if (collidedWithWallBottom) { //destrust ball and respawn on paddle and decrement life by 1
            *(pGame->getLives()) -= 1;
            this->setAttatched(1);
            this->MoveAttatchedBall();
            this->set_motion(0);
            this->setTrajectory(PI / 2);
            this->setIsFireBall(false);
            collidedWithWallBottom = false;
            //respawn ball on paddle
        }
        else if (lastcollidedBrick != nullptr && is_collided(uprLft.y, brickuprlft.y, uprLft.x, brickuprlft.x, -config.brickHeight, -this->height, config.brickWidth, this->width)) {
            if (!isFireBall) {

                point collisionPoint = CheckCollision(this, lastcollidedBrick);

                double relativeHitPoint;
                relativeHitPoint = (collisionPoint.x) - (lastcollidedBrick->getUprleft().x + config.brickWidth / 2.0);
                double normalizedHitPos = relativeHitPoint / (ptpaddle->getWidth() / 2.0);
                double newTheta = (PI / 2) - ((PI / 4) * normalizedHitPos);

                if ((uprLft.y + this->height) == brickuprlft.y) {
                    uprLft.y--;
                    thetta = newTheta;
                }
                else {
                    uprLft.y++;
                    thetta = -newTheta;
                };
            };
            collidedWithBrick = false;
            lastcollidedBrick = nullptr;
        };
    }

    //collision action with paddle
    else if (collidedWithPaddle) {
        point collisionPoint = CheckCollision(this, ptpaddle);
        cout << "collided with paddle";
        double relativeHitPoint;
        relativeHitPoint = (collisionPoint.x) - (ptpaddle->getUpperLeft().x + (ptpaddle->getWidth()) / 2.0);
        double normalizedHitPos = relativeHitPoint / (ptpaddle->getWidth() / 2.0);
        double newTheta = (PI / 2) - ((PI / 4) * normalizedHitPos);
        thetta = newTheta;
        collidedWithPaddle = false;
    }
    
    xt = 0;
    yt = 0;
    pGame->getGrid()->draw();

    return;
}   


void Ball::MoveAttatchedBall() {
    paddle* pPaddle = pGame->getPaddle();
    this->uprLft.x = pPaddle->getUpperLeft().x + pPaddle->getWidth()/2 - this->radius;
    this->uprLft.y = 480;
}