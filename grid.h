#pragma once

#include "drawable.h"
#include "Bricks.h"
#include "game.h"
#include "gameConfig.h"
#include <iostream>



class game;
class brick;
enum BrickType;

class grid:public drawable
{
	
	brick*** brickMatrix;		//2D array of brick pointers

	int rows, cols;
public:
	grid(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~grid();
	void draw() const;
	brick*** getMatrix();
	int getrows();
	int getcols();
	int addBrick(BrickType brkType, point clickedPoint);
	void delBrick(int gridCellRowIndex, int gridCellColIndex);
};

