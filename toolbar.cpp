#include "toolbar.h"
#include "game.h"
#include "grid.h"
#include "gameConfig.h"


////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
toolbarIcon::toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	drawable(r_uprleft, r_width, r_height, r_pGame)
{}




////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
iconAddNormalBrick::iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

////////////////////////////////////////////////////  class iconSaveLevel   //////////////////////////////////////////////

iconSaveLevel::iconSaveLevel(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconSaveLevel::onClick()
{
	//TO DO: add code for cleanup and game exit here

}

////////////////////////////////////////////////////  class iconDelBrick   //////////////////////////////////////////////

iconDelBrick::iconDelBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconDelBrick::onClick()
{

	//TO DO: add code for cleanup and game exit here


	pGame->printMessage("Click on bricks cells to delete  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->waitMouseClick(x, y);
	while (t == LEFT_CLICK)
	{	
		if (y > config.toolBarHeight) {

			point clicked;
			clicked.x = x;
			clicked.y = y;
			grid* pGrid = pGame->getGrid();
			if (pGame->getGrid()->getMatrix()[(clicked.y - uprLft.y) / config.brickHeight - 1][clicked.x / config.brickWidth] != NULL) {
				delete pGame->getGrid()->getMatrix()[(clicked.y - uprLft.y) / config.brickHeight - 1][clicked.x / config.brickWidth];
			};
			pGrid->draw();
			t = pGame->waitMouseClick(x, y);
		}
	}
	pGame->printMessage("");

}

////////////////////////////////////////////////////  class iconLoadLevel   //////////////////////////////////////////////

iconLoadLevel::iconLoadLevel(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconLoadLevel::onClick()
{
	//TO DO: add code for cleanup and game exit here

}
////////////////////////////////////////////////////  class iconPlay   //////////////////////////////////////////////

iconPlay::iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPlay::onClick()
{
	pGame->setMode(1);
	//TO DO: add code for cleanup and game exit here

}
////////////////////////////////////////////////////  class iconPause   //////////////////////////////////////////////

iconPause::iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPause::onClick()
{
	//TO DO: add code for cleanup and game exit here

}
////////////////////////////////////////////////////  class iconContinue   //////////////////////////////////////////////

iconContinue::iconContinue(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconContinue::onClick()
{
	//TO DO: add code for cleanup and game exit here

}

////////////////////////////////////////////////////  class iconStop   //////////////////////////////////////////////

iconStop::iconStop(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconStop::onClick()
{
	//TO DO: add code for cleanup and game exit here

}


void iconAddNormalBrick::onClick()
{

	pGame->printMessage("Click on empty cells to add Normal Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->waitMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_NRM, clicked);
		pGrid->draw();
		t = pGame->waitMouseClick(x, y);
	}
	pGame->printMessage("");

}

////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
iconExit::iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconExit::onClick()
{
	//TO DO: add code for cleanup and game exit here
}


////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(point r_uprleft, int wdth, int hght, game* pG) :
	drawable(r_uprleft, wdth, hght, pG)
{

	height = hght;
	pGame = pG;

	//First prepare List of images for each icon
	//To control the order of these images in the menu, reoder them in enum ICONS above	
	iconsImages[ICON_ADD_NORM] = "images\\ToolbarIcons\\NormalBrickIcon.jpg";
	iconsImages[ICON_SAVE] = "images\\ToolbarIcons\\SaveLevel.jpg";
	iconsImages[ICON_LOAD] = "images\\ToolbarIcons\\NormalBrickIcon.jpg";
	iconsImages[ICON_PLAY] = "images\\ToolbarIcons\\PlayIcon.jpg";
	iconsImages[ICON_PAUSE] = "images\\ToolbarIcons\\NormalBrickIcon.jpg";
	iconsImages[ICON_CONTINUE] = "images\\ToolbarIcons\\NormalBrickIcon.jpg";
	iconsImages[ICON_STOP] = "images\\ToolbarIcons\\NormalBrickIcon.jpg";
	iconsImages[ICON_EXIT] = "images\\ToolbarIcons\\ExitIcon.jpg";

	point p;
	p.x = 0;
	p.y = 0;

	iconsList = new toolbarIcon * [ICON_COUNT];

	//For each icon in the tool bar
	//	1- Create an object setting its upper left corner, width and height
	iconsList[ICON_ADD_NORM] = new iconAddNormalBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_LOAD] = new iconDelBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	//I REPLACED THE POSITIONS AND MADE THE "LOAD ICON" DO THE DELETE BRICK FUNCTION
	iconsList[ICON_SAVE] = new iconSaveLevel(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_PLAY] = new iconPlay(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_PAUSE] = new iconPause(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_CONTINUE] = new iconContinue(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_STOP] = new iconStop(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_EXIT] = new iconExit(p, config.iconWidth, height, pGame);

	//	2-Set its image (from the above images list)
	for (int i = 0; i < ICON_COUNT; i++)
	{
		iconsList[i]->setImageName(iconsImages[i]);

	}
}

toolbar::~toolbar()
{
	for (int i = 0; i < ICON_COUNT; i++)
		delete iconsList[i];
	delete iconsList;
}

void toolbar::draw() const
{
	for (int i = 0; i < ICON_COUNT; i++)
		iconsList[i]->draw();
	window* pWind = pGame->getWind();
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, height, pWind->GetWidth(), height);

}

//handles clicks on toolbar icons, returns true if exit is clicked
bool toolbar::handleClick(int x, int y)
{
	if (x > ICON_COUNT * config.iconWidth)	//click outside toolbar boundaries
		return false;


	//Check whick icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();	//execute onClick action of clicled icon

	if (clickedIconIndex == ICON_EXIT) return true;

	return false;


}

