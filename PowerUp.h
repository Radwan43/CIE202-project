#pragma once
#include "collidable.h"
#include "Bricks.h"
#include "game.h"

enum PowerType {

};

class Power :public collidable{
private:
	PowerType type;
public:
	Power(const point& r_uprleft, game* r_pGame,PowerType power);
	void movePower();
	//void collisionAction() override;

};