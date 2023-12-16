#include "paddle.h"
#include <iostream>
#include "game.h"
#include "gameConfig.h"

paddle::paddle(const point& r_uprleft, int r_width, int r_height, game* r_pGame) :
    collidable(r_uprleft, r_width, r_height, r_pGame),
    uprLft(r_uprleft),
    width(r_width),
    height(r_height)
{

    cout << "this was called in draw new";
    this->pGame->getWind()->DrawImage("images\\bricks\\NormalBrick.jpg", uprLft.x, getUpperLeft().y, 100, 20);
    this->draw();


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

void paddle::drawFirst() {
    while (int i = 0) {
        paddle* newpaddle = new normalpaddle(uprLft, 100, 20, this->pGame);
        newpaddle->draw();
        i++;
    }
}

void paddle::movePaddle(char key) {
    point newpos;
    
    Ball* pBall = pGame->getBall();
    window* pWin = this->pGame->getWind();
    int step=10;
    switch (key) {
    case 'A':
    case 'a':
        if(uprLft.x != 0){
            pWin->SetPen(LAVENDER, 1);
            pWin->SetBrush(LAVENDER);
            pWin->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + 100, uprLft.y + 20);
            if (pBall->isAttatched()) {
            pWin->DrawCircle(pBall->getUprleft().x + pBall->getRadius(), pBall->getUprleft().y + pBall->getRadius(), pBall->getRadius());

            }

            uprLft.x = uprLft.x - step;
            this->pGame->getWind()->SetPen(0.5, 0.1, 0.9, 0);
            this->pGame->getWind()->SetBrush(0.5, 0.1, 0.9);
            if (pBall->isAttatched()) {
                pBall->MoveAttatchedBall();
                pBall->draw();
            }
            this->pGame->getWind()->DrawImage("images\\bricks\\NormalBrick.jpg", uprLft.x, getUpperLeft().y, 100, 20);
            this->draw();
        }
        break;
    case 'D':
    case 'd':
        if (uprLft.x != 1100) {
            this->pGame->getWind()->SetPen(LAVENDER, 1);
            this->pGame->getWind()->SetBrush(LAVENDER);
            this->pGame->getWind()->DrawRectangle(uprLft.x, getUpperLeft().y, uprLft.x + 100, uprLft.y + 20);
            
            if (pBall->isAttatched()) {
                pWin->DrawCircle(pBall->getUprleft().x + pBall->getRadius(), pBall->getUprleft().y + pBall->getRadius(), pBall->getRadius());
            }

            uprLft.x = uprLft.x + step;

            this->pGame->getWind()->SetPen(0.5, 0.1, 0.9, 0);
            this->pGame->getWind()->SetBrush(0.5, 0.1, 0.9);

            if (pBall->isAttatched()) {
                pBall->MoveAttatchedBall();
                pBall->draw();
            }

            this->pGame->getWind()->DrawImage("images\\bricks\\NormalBrick.jpg", uprLft.x, getUpperLeft().y, 100, 20);
            this->draw();
        }
        break;
    }
}

normalpaddle::normalpaddle(const point& r_uprleft, int r_width, int r_height, game* r_pGame) :
    paddle({ r_uprleft.x-r_width/2,r_uprleft.y }, r_width, r_height, r_pGame)
{
        imageName = "images\\bricks\\NormalBrick.jpg";
      

}


void normalpaddle::collisionAction() {
    // Implement collision action for normalpaddle
}

void normalpaddle::draw() {
    cout << "this was called in draw new";
}



void paddle::draw() {

    while (int i = 0) {
        cout << "this was called in draw new";
        this->pGame->getWind()->DrawImage("images\\bricks\\NormalBrick.jpg", uprLft.x, getUpperLeft().y, 100, 20);
        this->drawable::draw();


      i++;
    }
}
