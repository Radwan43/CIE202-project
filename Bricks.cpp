#include "Bricks.h"


////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
brick::brick(point r_uprleft, int r_width, int r_height, game* r_pGame,BrickType type):
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
	this->type = type;
}

void brick::strengthCheck() {
	if (strength > 1) {
		strength--;
	}
	else {
		delete this;
	};
}

////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
normalBrick::normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame):
	brick(r_uprleft, r_width, r_height, r_pGame,BRK_NRM)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
	this->strength = 1;
}

void normalBrick::collisionAction()
{
	strengthCheck();
	//Add reflection

	//Add score change

	/*score++;*/
}


////////////////////////////////////////////////////  class hardBrick  /////////////////////////////////
hardBrick::hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_HRD)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
	this->strength = 3;
}

void hardBrick::collisionAction()
{
	strengthCheck();
	//Add reflection
	
	//Add score change

	/*score++;*/
}