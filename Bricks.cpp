#include "Bricks.h"


static std::vector<PowerUp> activePowerUps;

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

std::vector<PowerUp>* brick::getActivePowerUps()
{
	return &activePowerUps;
}

point brick::getUprleft() {
	return this->uprLft;
}

BrickType brick::getType() {
	return this->type;
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
	activePowerUps.push_back(PowerUp(uprLft, pGame));

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
}

////////////////////////////////////////////////////  class lifeBrick  /////////////////////////////////
lifeBrick::lifeBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_LIF)
{
	imageName = "images\\bricks\\LifeBrick.jpg";
	this->strength = 1;
}

void lifeBrick::collisionAction()
{
	//score change
	*(pGame->getScore()) += 1;
	//life change
	*(pGame->getLives()) += 1;
	//strength check	
	strengthCheck();
}

////////////////////////////////////////////////////  class rockBrick  /////////////////////////////////
rockBrick::rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_RCK)
{
	imageName = "images\\bricks\\RockBrick.jpg";
	this->strength = -1;
}

void rockBrick::collisionAction()
{}

////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
bombBrick::bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame, BRK_BMB)
{
	imageName = "images\\bricks\\BombBrick.jpg";
	this->strength = 1;
}

void bombBrick::collisionAction()
{
	//score change
	*(pGame->getScore()) += 4;
	//destruct touching bricks
	int row = (uprLft.y - config.toolBarHeight) / config.brickHeight;
	int col = uprLft.x / config.brickWidth;
	brick*** brickMatrix = pGame->getGrid()->getMatrix();
	int maxRow = pGame->getGrid()->getrows();
	int maxCol = pGame->getGrid()->getcols();
	for (int i = row - 1; i <= row + 1; i++) {
		if (i >= 0 && i < maxRow) {
			for (int j = col - 1; j <= col + 1; j++) {
				if (j >= 0 && j < maxCol) {

					if (brickMatrix[i][j]) {
						delete brickMatrix[i][j];
					}
				};
			}
		};
	}
}
