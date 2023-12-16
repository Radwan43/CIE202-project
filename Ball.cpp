#include "ball.h"


Ball::Ball(point r_uprleft, int r_radius, game* r_pGame) :
    collidable({ r_uprleft.x - r_radius ,r_uprleft.y }, 2 * r_radius, 2 * r_radius, r_pGame, "circle"),
    radius(r_radius)
{
    thetta = PI/2;

    life = 3;

    speed = 4;
    xt = 0;
    yt = 0;

    ptpaddle = pGame->getPaddle();
    lastcollidedBrick = nullptr;
    moving = 0;
    attatched = 1;
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

int Ball::getLife() {
    return life;
}
void Ball::moveBall() {

    if (moving == 1) {
        window* pWin = pGame->getWind();

        //for (int i = 0; i < 10; i++) {
        pWin->SetBrush(config.bkGrndColor);
        pWin->SetPen(config.bkGrndColor, 1);
        pWin->DrawCircle(uprLft.x + radius, uprLft.y + radius, radius);
        xt += speed * cos(thetta);
        yt += speed * sin(thetta);
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
                        collidedWithBrick = true;
                        lastcollidedBrick = pGame->getGrid()->getMatrix()[row][col];
                        this->collisionAction();
                        pGame->getGrid()->getMatrix()[row][col]->collisionAction();
                        break;
                    }
                }
            }
        }
        // Check collisions with paddle
        if ((CheckCollision(this, ptpaddle).x != 0 ) ) {
            collidedWithPaddle = true;
            cout << "collided with paddle";
            this->collisionAction();
        }
        // Check collisions with walls
        else if (uprLft.y <= config.toolBarHeight) {
            collidedWithWallTop = true;
            this->collisionAction();
        }
        else if (uprLft.x <= config.statusBarHeight+2*radius) {
            collidedWithWallLeft = true;
            this->collisionAction();
        }
        else if (uprLft.x + radius*2 >= pGame->getWind()->GetWidth()) {
            collidedWithWallRight = true;
            this->collisionAction();
        }
        else if (uprLft.y + radius*2 >= pGame->getWind()->GetHeight()) {
            collidedWithWallBottom = true;
            this->collisionAction();
        }




        draw();
        std::this_thread::sleep_for(std::chrono::nanoseconds(500000));


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
        if ((lastcollidedBrick->getUprleft().x == uprLft.x) && (lastcollidedBrick->getUprleft().y == uprLft.y)) { topLcol = true; }
        else if ((lastcollidedBrick->getUprleft().x == (uprLft.x + radius)) && (lastcollidedBrick->getUprleft().y == (uprLft.y))) { topRcol = true; }
        else if ((lastcollidedBrick->getUprleft().x == (uprLft.x + radius)) && (lastcollidedBrick->getUprleft().y == (uprLft.y + radius))) { bottomRcol = true; }
        else if ((lastcollidedBrick->getUprleft().x == (uprLft.x)) && (lastcollidedBrick->getUprleft().y == (uprLft.y + radius))) { bottomLcol = true; }
    }

    //collision action with bricks and walls
    if (topLcol || topRcol || bottomLcol || bottomRcol) {
        thetta = PI + thetta;
        topLcol= topRcol= bottomLcol= bottomRcol = false;
        collidedWithBrick = false;
    }
    else if (collidedWithBrick || collidedWithWallBottom || collidedWithWallLeft || collidedWithWallRight || collidedWithWallTop) {
        if (collidedWithWallLeft || collidedWithWallRight || lastcollidedBrick!=nullptr &&(is_collided(uprLft.x, lastcollidedBrick->getUprleft().x, uprLft.y, lastcollidedBrick->getUprleft().y, radius, 60, radius, 30))) {
			thetta = PI - thetta; // Reflect horizontally
			collidedWithWallRight= collidedWithWallLeft = collidedWithBrick= false;
            lastcollidedBrick = nullptr;

		}
        else if (collidedWithWallTop || lastcollidedBrick != nullptr && is_collided(uprLft.y, lastcollidedBrick->getUprleft().y, uprLft.x, lastcollidedBrick->getUprleft().x, -30, -radius, 60, radius)) {
            thetta = -thetta; // Reflect vertically
            collidedWithWallTop = collidedWithBrick=false;
            lastcollidedBrick = nullptr;
        }
        else if (collidedWithWallBottom) { //destrust ball and respawn on paddle and decrement life by 1
            //life --
            this->setAttatched(1);
            this->MoveAttatchedBall();
            this->set_motion(0);
            this->setTrajectory(PI / 2);

            collidedWithWallBottom = false;
            //respawn ball on paddle
        }
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
    //this->moveBall();
    // Implement collision action for normalpaddle
    // Implement collision action for walls
    // Implement collision action with bricks
    // Implement collision action with bottom (respawn ball attatched to paddle, life--)
}


void Ball::MoveAttatchedBall() {
    paddle* pPaddle = pGame->getPaddle();
    this->uprLft.x = pPaddle->getUpperLeft().x + pPaddle->getWidth()/2 - this->radius;
    this->uprLft.y = 480;
}