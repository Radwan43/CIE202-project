#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "grid.h"
#include "paddle.h"
#include "Ball.h"
#include <iostream>
#include "gameConfig.h"

class grid;
class Ball;
//Main class that coordinates the game operation
class game
{

	enum MODE	//Game mode
	{
		MODE_DSIGN,	//Desing mode (startup mode)
		MODE_PLAY	//Playing mode
	};

	MODE gameMode;

	/// Add more members if needed



	window* pWind;	//Pointer to the CMU graphics window
	toolbar* gameToolbar;
	grid* bricksGrid;
	normalpaddle* thepaddle;
	Ball* ball;

public:
	game();
	~game();

	//Get coordinate where user clicks and returns click type (left/right)
	clicktype getMouseClick(int& x, int& y) const;
	keytype getKeyboardClick(char& key) const;
	string getSrting() const;	 //Returns a string entered by the user


	window* CreateWind(int, int, int, int) const; //creates the game window


	void clearStatusBar() const;	//Clears the status bar


	void printMessage(string msg) const;	//Print a message on Status bar

	void go() const;

	window* getWind() const;		//returns a pointer to the graphics window

	void movePaddle();

	grid* getGrid() const;

	// add the ball

	// add the platform 

};

