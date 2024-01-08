#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "grid.h"
#include "paddle.h"
#include "Ball.h"
#include <iostream>
#include "gameConfig.h"
#include "GameTimer.h"

class grid;
class Ball;

enum MODE	//Game mode
{
	MODE_DSIGN,	//Desing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_PAUSE
};

//Main class that coordinates the game operation
class game
{


	MODE* gameMode;

	/// Add more members if needed



	window* pWind;	//Pointer to the CMU graphics window
	toolbar* gameToolbar;
	grid* bricksGrid;
	paddle* thepaddle;
	Ball* ball;
	const string lives= "Lives: ";
	const string score = "Score: ";
	const string time = "Time (s): ";
	int* livesPtr;
	int* scorePtr;
	int* timePtr;
	int* scoremultiplier;

public:
	game();
	~game();

	//Get coordinate where user clicks and returns click type (left/right)
	clicktype waitMouseClick(int& x, int& y) const;
	keytype waitKeyboardClick(char& key) const;
	string getSrting() const;	 //Returns a string entered by the user


	window* CreateWind(int, int, int, int) const; //creates the game window

	int* getScore()const;

	int* getTimer()const;
	int* getLives()const;

	void clearStatusBar() const;	//Clears the status bar


	void printMessage(string msg) const;	//Print a message on Status bar

	void go() const;

	window* getWind() const;		//returns a pointer to the graphics window

	void setMode(MODE gameMode) const;
	
	MODE getMode()const;

	grid* getGrid() const;

	paddle* getPaddle() const;

	Ball* getBall() const;

	void setScoreMultiplier(int multiplier) const;

	int getScoreMultiplier() const;

	// add the ball

	// add the platform 

};

