#include "paddle.h"
#include <iostream>
paddle::paddle(const point& r_uprleft, int r_width, int r_height, game* r_pGame) :
    collidable(r_uprleft, r_width, r_height, r_pGame),
    uprLft(r_uprleft),
    width(r_width),
    height(r_height)
{
}


point paddle::getUpperLeft() const {
    return uprLft;
}

void paddle::setUpperLeft(const point& r_uprleft) {
    uprLft = r_uprleft;
}

int paddle::getWidth() const {
    return width;
}

void paddle::setWidth(int r_width) {
    width = r_width;
}

int paddle::getHeight() const {
    return height;
}

void paddle::setHeight(int r_height) {
    height = r_height;
}

void paddle::movePaddle(char key, paddle* paddle) {
    point newpos;
    cout << "move paddle was called";
    cout << this->getUpperLeft().x;
    switch (key) {
    case 'A':
    case 'a':
        newpos.x = uprLft.x - 10;
        newpos.y = uprLft.y;
        paddle->setUpperLeft(newpos);
        paddle->draw();
        break;
    case 'D':
    case 'd':
        newpos.x = uprLft.x + 10;
        newpos.y = uprLft.y;
        this->setUpperLeft(newpos);
        paddle->draw();
        break;
    }
}

normalpaddle::normalpaddle(const point& r_uprleft, int r_width, int r_height, game* r_pGame) :
    paddle(r_uprleft, r_width, r_height, r_pGame)
{
    imageName = "images\\bricks\\NormalBrick.jpg";
}


void normalpaddle::collisionAction() {
    // Implement collision action for normalpaddle
}
