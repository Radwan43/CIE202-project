#include "ball.h"


PowerUps::PowerUps(point r_uprleft, game* r_pGame) :
    collidable(r_uprleft, 25, 25, r_pGame){

    speed = 3;
    xt = 0;
    yt = 0;

    moving = 0;
}

bool PowerUps::isMoving() {
    return this->moving;
}


point PowerUps::getUprleft() {
    return uprLft;
}

void PowerUps::set_motion(bool moving) {
    this->moving = moving;
}


void PowerUps::setSpeed(double speed) {
    this->speed = speed;
}

void PowerUps::movePowerUp() {

    if (moving == 1) {
        window* pWin = pGame->getWind();

        int br = 0;
        pWin->SetBrush(config.bkGrndColor);
        pWin->SetPen(config.bkGrndColor, 1);
        pWin->DrawCircle(uprLft.x - 25, uprLft.y - 25, 25);
        xt -= speed;
        yt -= speed;
        if (abs(xt) >= 1) {
            this->uprLft.x += xt;
            xt -= int(xt);
        };
        if (abs(yt) >= 1) {
            this->uprLft.y -= yt;
            yt -= int(yt);
        };


        draw();
        std::this_thread::sleep_for(std::chrono::nanoseconds(500000));


    }
}




void PowerUps::collisionAction() {
    return;
}

