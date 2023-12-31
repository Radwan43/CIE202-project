#include "game.h"

enum MODE;

static std::vector<PowerUp>* activePowerUps;

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

	//7- Create the score, time, and lives
	timePtr = new int;
	*timePtr = 0;
	livesPtr = new int;
	*livesPtr = 3;
	scorePtr = new int;
	*scorePtr = 0;
	scoremultiplier = new int;
	*scoremultiplier = 1;


	
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


void game::setScoreMultiplier(int multiplier) const {
	*scoremultiplier = multiplier;
}

int game::getScoreMultiplier() const {
	return *scoremultiplier;
}

keytype game::waitKeyboardClick(char& key) const{
	point newpos;
	newpos.x = 10;
	newpos.y = 10;
	

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

void game::setMode(MODE gameMode) const {
	*this->gameMode = gameMode;
}

MODE game::getMode()const {
	return *(this->gameMode);
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



int* game::getScore() const {
	return scorePtr;
}



int* game::getTimer() const {
	return timePtr;
}


int* game::getLives() const {
	return livesPtr;
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


	GameTimer gameTimer;
	do
	{	

		pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click


		if (*gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		{
			printMessage("Ready...");
			//[1] If user clicks on the Toolbar

			this->gameToolbar->draw();
			this->bricksGrid->draw();
			if (y >= 0 && y < config.toolBarHeight)
			{
				isExit = gameToolbar->handleClick(x, y);
			}
		}
		if (*gameMode == MODE_PLAY) {
			this->gameToolbar->draw();
			this->bricksGrid->draw();
			pWind->FlushKeyQueue();
			pWind->FlushMouseQueue();

			pWind->SetPen(RED, 1);
			pWind->SetBrush(RED);
			pWind->DrawImage("images\\lifeheart.jpg", 150, 10, 20, 20);
			pWind->DrawImage("images\\lifeheart.jpg", 180, 10, 20, 20);
			pWind->DrawImage("images\\lifeheart.jpg", 210, 10, 20, 20);
			printMessage("Play!");
			while (true) {




				if (*livesPtr == 2) {
					pWind->SetPen(config.statusBarColor, 1);
					pWind->SetBrush(config.statusBarColor);
					pWind->DrawRectangle(210, 10, 240, 30);
				}
				else if (*livesPtr == 1) {
					pWind->SetPen(config.statusBarColor, 1);
					pWind->SetBrush(config.statusBarColor);
					pWind->DrawRectangle(180, 10, 210, 30);
				}
				else if (*livesPtr == 0) {
					pWind->SetPen(config.statusBarColor, 1);
					pWind->SetBrush(config.statusBarColor);
					pWind->DrawRectangle(150, 10, 180, 30);
				}

				pWind->SetPen(config.statusBarColor, 1);
				pWind->SetBrush(config.statusBarColor);
				pWind->DrawRectangle(300, 10, 550, 40);
				pWind->SetPen(config.penColor, 50);
				pWind->SetFont(24, BOLD, BY_NAME, "Arial");
				pWind->DrawString(300, 10, gameTimer.getElapsedTimeString());
				pWind->DrawString(450, 10, "score: "+std::to_string(*scorePtr));





				if (!ball->isAttatched()&&!ball->isMoving()) {
					ball->set_motion(true);
				}

				pWind->GetMouseClick(x, y);
				if (y >= 0 && y < config.toolBarHeight)
				{
					isExit = gameToolbar->handleClick(x, y);
				};
				ktype = pWind->GetKeyPress(Key);
				switch (ktype) {
				case ESCAPE:
					*gameMode = MODE_DSIGN;
					break;

				case ASCII:
					if (Key == ' ') {
						if (*gameMode != MODE_PLAY)
							*gameMode = MODE_PLAY;
						if (!ball->isMoving()) {
							ball->set_motion(1);
							ball->setAttatched(0);
						}
						if (!gameTimer.isRunning()) {
							gameTimer.start();
						}
					}
					else if (Key == 'q' || Key == 'Q') {
						if (*gameMode != MODE_PAUSE) {
							*gameMode = MODE_PAUSE;
							if (ball->isMoving())
								ball->set_motion(false);
						};
						if (gameTimer.isRunning()) {
							gameTimer.pause();
						}
					}
					break;
				}



				ball->moveBall();

				
				
				thepaddle->movePaddle(Key);


				activePowerUps = brick::getActivePowerUps();

				for (PowerUp& powerUp : *activePowerUps) {
					powerUp.movePowerUp();

					if (powerUp.CheckCollision(&powerUp, thepaddle).y != 0) {
						powerUp.collisionAction();

					
					}
					powerUp.disable(&gameTimer);
				}


				int BrickNumber = 0;
				
				for (int row = 0; row < bricksGrid->getrows(); row++) {
					for (int col = 0; col < bricksGrid->getcols(); col++) {
						if ((bricksGrid->getMatrix()[row][col]!=nullptr)&& bricksGrid->getMatrix()[row][col]->getType()!=BRK_RCK) {
							BrickNumber++;
						}
					}
				}

				if (*livesPtr == 0) {
					//GAME OVER SEQUENCE
					string scoreSTR = to_string(*scorePtr);
					printMessage("GAME OVER! Your score is: " + scoreSTR);
					*gameMode = MODE_DSIGN;
				};

				if (BrickNumber == 0) {
					//END GAME SEQUENCE
					string scoreSTR = to_string(*scorePtr);
					printMessage("Congrats! You finished the level! Your score is: " + scoreSTR);
					*gameMode = MODE_DSIGN;
					
				};

				if (*gameMode == MODE_DSIGN) {
					ball->setAttatched(1);
					ball->set_motion(false);
					*livesPtr=3;
					ball->setTrajectory(ball->getPI() / 2);
					ball->setSpeed(4);
					thepaddle->CentrePaddle();
					*scorePtr = 0;
					

					break;
				}





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
