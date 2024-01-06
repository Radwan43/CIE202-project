#include "Bricks.h"


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
	//score change
	*(pGame->getScore()) += 1;
	//strength check	
	strengthCheck();
}


////////////////////////////////////////////////////  class hardBrick  /////////////////////////////////
hardBrick::hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_HRD)
{
	imageName = "images\\bricks\\HardBrick.jpg";
	this->strength = 3;
}

void hardBrick::collisionAction()
{	
	//score change
	*(pGame->getScore())+=1;
	//strength check	
	strengthCheck();
	//Add reflection
	
	//score change
	pGame->setScore(pGame->getScore() + 1);
}

////////////////////////////////////////////////////  class rockBrick  /////////////////////////////////
rockBrick::rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_RCK)
{
	imageName = "images\\bricks\\RockBrick.jpg";
	this->strength = 5;
}

void rockBrick::collisionAction()
{
	//Add reflection
}

////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
bombBrick::bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_BMB)
{
	imageName = "images\\bricks\\BombBrick.jpg";
	this->strength = 1;
}

void bombBrick::collisionAction()
{
	strengthCheck();
	//Add reflection

	//Add score change
	pGame->setScore(pGame->getScore() + 4);
	//Add explosion
}