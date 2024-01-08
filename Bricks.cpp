#include "Bricks.h"
#include "PowerUps.h"

////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
brick::brick(point r_uprleft, int r_width, int r_height, game* r_pGame,BrickType type):
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
	this->type = type;
}

brick::~brick() {
	int gridCellRowIndex = (uprLft.y-config.toolBarHeight) / config.brickHeight;
	int gridCellColIndex = uprLft.x / config.brickWidth;
	pGame->getGrid()->delBrick(gridCellRowIndex, gridCellColIndex);
}

void brick::strengthCheck() {
	if (strength > 1) {
		strength--;
	}
	else {
		delete this;
	};
}

point brick::getUprleft() {
	return this->uprLft;
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

	PowerUps fireball(getUprleft(), pGame);
	//fireball.se(true);

	//Add score change
	//pGame->setScore(pGame->getScore() + 1);
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
	
	//score change
	//pGame->setScore(pGame->getScore() + 1);
}

fireBrick::fireBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_FIRE)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
	this->strength = 1;
}

void fireBrick::collisionAction()
{
	strengthCheck();



	//score change
	//pGame->setScore(pGame->getScore() + 1);
}

movementBrick::movementBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_MVMNT)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
	this->strength = 1;
}

void movementBrick::collisionAction()
{
	strengthCheck();
	//Add reflection

	//score change
	//pGame->setScore(pGame->getScore() + 1);
}

sizeBrick::sizeBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_SIZE)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
	this->strength = 1;
}

void sizeBrick::collisionAction()
{
	strengthCheck();
	//Add reflection

	//score change
	//pGame->setScore(pGame->getScore() + 1);
}
