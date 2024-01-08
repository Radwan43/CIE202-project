#pragma once
#include "collidable.h"

class paddle : public collidable {

private:
    bool inverted = 0;
    int speed = 10;
public:
    paddle(const point& r_uprleft, int r_width, int r_height, game* r_pGame);

    point getUpperLeft() const;
    void setUpperLeft(const point& r_uprleft);

    int getWidth() const;
    void setWidth(int r_width);

    int getHeight() const;
    void setHeight(int r_height);

    void drawFirst();
    void draw();

    void movePaddle(char key);

    void CentrePaddle();
    void setInverted(bool r_inverted);
    void setSpeed(int r_speed);

};

class normalpaddle : public paddle {
public:
    normalpaddle(const point& r_uprleft, int r_width, int r_height, game* r_pGame);

     void collisionAction() override;
     void draw();
};
