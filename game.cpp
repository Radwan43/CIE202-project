#include "game.h"

enum MODE;

game* thisGame; 
game::game()
{
	thisGame = this;
	//Initialize playgrond parameters
	gameMode = new MODE(MODE_DSIGN);


	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//2 - create and draw the toolbar
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;

	gameToolbar = new toolbar(toolbarUpperleft, 0, config.toolBarHeight, this);
	gameToolbar->draw();

	//3 - create and draw the grid
	point gridUpperleft;
	gridUpperleft.x = 0;
	gridUpperleft.y = config.toolBarHeight;
	bricksGrid = new grid(gridUpperleft, config.windWidth, config.gridHeight, this);
	bricksGrid->draw();

	//4- Create the Paddle
	//TODO: Add code to create and draw the paddle
	thepaddle = new normalpaddle({ config.windWidth / 2 , 500 }, 100, 20, this);
	thepaddle->draw();

	//5- Create the ball
	//TODO: Add code to create and draw the ball
	ball = new Ball({ config.windWidth / 2 , 480}, 10, this);
	ball->draw();

	//6- Create and clear the status bar
	clearStatusBar();
}

game::~game()
{
	delete pWind;
	delete gameToolbar;
	delete bricksGrid;
}


clicktype game::waitMouseClick(int& x, int& y) const
{
	return pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

void game::movePaddle() {
	thisGame->getWind()->SetPen(LAVENDER, 1);
	thisGame->getWind()->SetBrush(LAVENDER);
	point point = { 200,500 };
	thisGame->getWind()->DrawRectangle(point.x, point.y, 100, 20);

}


keytype game::waitKeyboardClick(char& key) const{
	point newpos;
	newpos.x = 10;
	newpos.y = 10;
	
	//paddle* newpaddle = new normalpaddle(newpos, 100, 20, thisGame);
	//newpaddle->draw();
	//delete thepaddle;
	return pWind->WaitKeyPress(key);
}
//////////////////////////////////////////////////////////////////////////////////////////
window* game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}



window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}

void game::setMode(int gameMode) const {//0 for design mode 1 for play mode
	*this->gameMode = MODE(gameMode);
}

int game::getMode()const {
	return int(*this->gameMode);
}

string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return bricksGrid;
}

paddle* game::getPaddle() const {
	return this->thepaddle;
}

Ball* game::getBall() const {
	return ball;
}


////////////////////////////////////////////////////////////////////////
void game::go() const
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;
	char k;
	char Key;
	keytype ktype;

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Brick Breaker (CIE202-project) - - - - - - - - - -");
	//int i = 0;

	GameTimer gameTimer;
	gameTimer.start();

	do
	{	
		//getKeyboardClick(Key);
		printMessage("Ready...");
		//thepaddle->movePaddle(Key, thepaddle);

		pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
		//if (i == 1) { *gameMode = MODE_PLAY; }
		//else { *gameMode = MODE_DSIGN; };

		if (*gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		{
			//[1] If user clicks on the Toolbar
			this->bricksGrid->draw();
			if (y >= 0 && y < config.toolBarHeight)
			{
				isExit = gameToolbar->handleClick(x, y);
			}
		}
		if (*gameMode == MODE_PLAY) {
			this->bricksGrid->draw();
			printMessage("Play!");
			while (true) {



					pWind->SetPen(RED,1);
					pWind->SetBrush(RED);
					pWind->DrawRectangle(700 , 10, 10 + 700, 20);
					pWind->DrawRectangle(720, 10, 10 + 720, 20);
					pWind->DrawRectangle(740, 10, 10 + 740, 20);

					pWind->SetPen(LAVENDER, 1);
					pWind->SetBrush(LAVENDER);
					pWind->DrawRectangle(900, config.toolBarHeight - 20, 920, 40);
					pWind->SetPen(config.penColor, 50);
					pWind->SetFont(24, BOLD, BY_NAME, "Arial");
					pWind->DrawString(900, config.toolBarHeight - 20, gameTimer.getElapsedTimeString());
					//pWind->SetPen(LAVENDER, 1);
					//pWind->SetBrush(LAVENDER);
					//pWind->DrawRectangle(900, config.toolBarHeight - 20, 920, 50);


				/*	if (ball->getLife() = 2) {

						pWind->SetPen(RED, 1);
						pWind->SetBrush(RED);
						pWind->DrawRectangle(740, 10, 10 + 740, 20);

					}*/
				
				//pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
				ktype = pWind->GetKeyPress(Key);
				switch (ktype) {
				case ESCAPE:
					*gameMode = MODE_DSIGN;
					break;

				case ASCII:
					if (Key == ' ') {
						if (!ball->isMoving()) {
							ball->set_motion(1);
							ball->setAttatched(0);
						}
						break;
					}
					break;
				}

				ball->moveBall();

				thepaddle->movePaddle(Key);

				if (*gameMode == MODE_DSIGN) break;



				//create paddle and ball here
				//Allow movement of paddle and ball
				//change toolbar to only show pause, score, lives, time
				//Press space to launch ball 
				//paint over grid lines
				//press escape to return (delete ball and paddle)
				//pWind->GetKeyPress
			}
		}

	} while (!isExit);

}
