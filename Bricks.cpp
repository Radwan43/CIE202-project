#include "Bricks.h"


static std::vector<PowerUp> activePowerUps;

////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
brick::brick(point r_uprleft, int r_width, int r_height, game* r_pGame, BrickType type) :
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
	this->type = type;
}

brick::~brick() {
	int gridCellRowIndex = (uprLft.y - config.toolBarHeight) / config.brickHeight;
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

std::vector<PowerUp>* brick::getActivePowerUps()
{
	return &activePowerUps;
}

point brick::getUprleft() {
	return this->uprLft;
}


////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
normalBrick::normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_NRM)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
	this->strength = 1;

}

void normalBrick::collisionAction()
{
	activePowerUps.push_back(PowerUp(uprLft, pGame));

	//score change
	//strength check	
	strengthCheck();
	pGame->incScore();

}


////////////////////////////////////////////////////  class hardBrick  /////////////////////////////////
hardBrick::hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_HRD)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
	this->strength = 3;

	pGame->incScore();
}

void hardBrick::collisionAction()
{
	//score change
	//strength check	
	strengthCheck();
}
