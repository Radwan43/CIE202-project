#pragma once
#include "gameConfig.h"
#include "game.h"

//This file contains all classes bricks classes 
#include "collidable.h"

enum BrickType	//add more brick types
{
	BRK_NRM,	//Normal Brick
	BRK_HRD,	//Hard Brick
	BRK_RCK,	//Rock Brick
	BRK_BMB 	//Bomb Brick

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
	~brick();
	point getUprleft();
	BrickType getType() { return type; }
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

////////////////////////////////////////////////////  class rockBrick  /////////////////////////////////
class rockBrick :public brick
{
public:
	rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};


////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
class bombBrick :public brick
{
public:
	bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};