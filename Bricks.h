#pragma once
#include "gameConfig.h"
#include "game.h"
#include "PowerUp.h"
//This file contains all classes bricks classes 
#include "collidable.h"
#include <vector>


enum BrickType	//add more brick types
{
	BRK_NRM,	//Normal Brick
	BRK_HRD		//Hard Brick

	//TODO: Add more types
};

////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
//Base class for all bricks
class PowerUp;
class brick :public collidable
{
private:
	BrickType type;
protected:
	int strength{};
public:
	brick(point r_uprleft, int r_width, int r_height, game* r_pGame,BrickType type);
	void strengthCheck();
	static std::vector<PowerUp>* getActivePowerUps();
	~brick();
	point getUprleft();
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

