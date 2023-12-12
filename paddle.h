#pragma once
#include "collidable.h"

class paddle : public collidable {
public:
    paddle(const point& r_uprleft, int r_width, int r_height, game* r_pGame);

    point getUpperLeft() const;
    void setUpperLeft(const point& r_uprleft);

    int getWidth() const;
    void setWidth(int r_width);

    int getHeight() const;
    void setHeight(int r_height);

    void movePaddle(char key, paddle* paddle);

private:
    point uprLft;
    int width;
    int height;
};

class normalpaddle : public paddle {
public:
    normalpaddle(const point& r_uprleft, int r_width, int r_height, game* r_pGame);

     void collisionAction() override;
};
