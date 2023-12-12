#pragma once

//This file contains all classes bricks classes 
#include "collidable.h"

enum BrickType	//add more brick types
{
	BRK_NRM,	//Normal Brick
	BRK_HRD		//Hard Brick

	//TODO: Add more types
};

////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
//Base class for all bricks
class brick :public collidable
{
private:
	BrickType type;
protected:
	int strength{};
public:
	brick(point r_uprleft, int r_width, int r_height, game* r_pGame,BrickType type);
	void strengthCheck();
};


////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
class normalBrick :public brick
{
public:
	normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};

////////////////////////////////////////////////////  class hardBrick  /////////////////////////////////
class hardBrick :public brick
{
public:
	hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};
