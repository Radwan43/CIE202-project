#include "grid.h"


grid::grid(point r_uprleft, int wdth, int hght, game* pG):
	drawable(r_uprleft, wdth, hght, pG)
{

	rows = height / config.brickHeight;
	cols = width / config.brickWidth;

	brickMatrix = new brick ** [rows];
	for (int i = 0; i < rows; i++)
		brickMatrix[i] = new brick * [cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			brickMatrix[i][j] = nullptr;
}

grid::~grid()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				delete brickMatrix[i][j];	//delete all allocated bricks

	for (int i = 0; i < rows; i++)
		delete brickMatrix[i];

	delete brickMatrix;

}

void grid::draw() const
{	
	if (pGame->getMode() == MODE_DSIGN) {

		window* pWind = pGame->getWind();
		//draw lines showing the grid
		pWind->SetPen(config.gridLinesColor, 1);

		//draw horizontal lines
		for (int i = 0; i < rows; i++) {
			int y = uprLft.y + (i + 1) * config.brickHeight;
			pWind->DrawLine(0, y, width, y);
		}
		//draw vertical lines
		for (int i = 0; i < cols; i++) {
			int x = (i + 1) * config.brickWidth;
			pWind->DrawLine(x, uprLft.y, x, uprLft.y + rows * config.brickHeight);
		}
	}
	else if (pGame->getMode() == MODE_PLAY) {

		window* pWind = pGame->getWind();
		//draw lines showing the grid
		pWind->SetPen(config.bkGrndColor, 1);

		//draw horizontal lines
		for (int i = 0; i < rows; i++) {
			int y = uprLft.y + (i + 1) * config.brickHeight;
			pWind->DrawLine(0, y, width, y);
		}
		//draw vertical lines
		for (int i = 0; i < cols; i++) {
			int x = (i + 1) * config.brickWidth;
			pWind->DrawLine(x, uprLft.y, x, uprLft.y + rows * config.brickHeight);
		}
	};

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				brickMatrix[i][j]->draw();	//draw exisiting bricks
}

brick*** grid::getMatrix() { 
	return brickMatrix; 
}

int grid::getrows() {
	return this->rows;
}
int grid::getcols() {
	return this->cols;
}

int grid::addBrick(BrickType brkType, point clickedPoint)
{
	//TODO:
	// 1- Check that the clickedPoint is within grid range (and return -1)
	// 2- Check that the clickedPoint doesnot overlap with an exisiting brick (return 0)

	//Here we assume that the above checks are passed
	
	//From the clicked point, find out the index (row,col) of the corrsponding cell in the grid
	int gridCellRowIndex = (clickedPoint.y-uprLft.y) / config.brickHeight;
	int gridCellColIndex = clickedPoint.x / config.brickWidth;

	//Now, align the upper left corner of the new brick with the corner of the clicked grid cell
	point newBrickUpleft;
	newBrickUpleft.x = uprLft.x + gridCellColIndex * config.brickWidth;
	newBrickUpleft.y = uprLft.y+ gridCellRowIndex * config.brickHeight;

	switch (brkType)
	{
	case BRK_NRM:	//The new brick to add is Normal Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new normalBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_HRD:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new hardBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_RCK:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new rockBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_BMB:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new bombBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_LIF:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new lifeBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_PWR:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new powerBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	}
	return 1;
}

void grid::delBrick(int gridCellRowIndex, int gridCellColIndex) {
	brickMatrix[gridCellRowIndex][gridCellColIndex] = nullptr;
	window* pW = pGame->getWind();
	point brickPoint;
	brickPoint.x= uprLft.x + gridCellColIndex * config.brickWidth;
	brickPoint.y= uprLft.y + gridCellRowIndex * config.brickHeight;
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(brickPoint.x, brickPoint.y, brickPoint.x+config.brickWidth, brickPoint.y+config.brickHeight);
	cout << endl<<"brick deleted" << endl;

	
}
