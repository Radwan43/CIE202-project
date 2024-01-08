#include "toolbar.h"
#include "game.h"
#include "grid.h"
#include "gameConfig.h"
#include <fstream>
using namespace std;

////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
toolbarIcon::toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	drawable(r_uprleft, r_width, r_height, r_pGame)
{}




////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
iconAddNormalBrick::iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

////////////////////////////////////////////////////  class iconAddHardBrick   //////////////////////////////////////////////
iconAddHardBrick::iconAddHardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconAddHardBrick::onClick()
{	
	if (pGame->getMode() == MODE_DSIGN) {

		pGame->printMessage("Click on empty cells to add Hard Bricks  ==> Right-Click to stop <==");
		int x, y;
		clicktype t = pGame->waitMouseClick(x, y);
		while (t == LEFT_CLICK)
		{
			point clicked;
			clicked.x = x;
			clicked.y = y;
			if (y > config.toolBarHeight && y < config.gridHeight + config.toolBarHeight) {
				grid* pGrid = pGame->getGrid();
				pGrid->addBrick(BRK_HRD, clicked);
				pGrid->draw();
			};
			t = pGame->waitMouseClick(x, y);
		}
		pGame->printMessage("");
	};
}

////////////////////////////////////////////////////  class iconAddRockBrick   //////////////////////////////////////////////
iconAddRockBrick::iconAddRockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconAddRockBrick::onClick()
{
	if (pGame->getMode() == MODE_DSIGN) {
		pGame->printMessage("Click on empty cells to add Rock Bricks  ==> Right-Click to stop <==");
		int x, y;
		clicktype t = pGame->waitMouseClick(x, y);
		while (t == LEFT_CLICK)
		{
			point clicked;
			clicked.x = x;
			clicked.y = y;
			if (y > config.toolBarHeight && y < config.gridHeight + config.toolBarHeight) {

				grid* pGrid = pGame->getGrid();
				pGrid->addBrick(BRK_RCK, clicked);
				pGrid->draw();
			};
			t = pGame->waitMouseClick(x, y);
		}
		pGame->printMessage("");
	}
}

////////////////////////////////////////////////////  class iconAddBombBrick   //////////////////////////////////////////////
iconAddBombBrick::iconAddBombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconAddBombBrick::onClick()
{
	if (pGame->getMode() == MODE_DSIGN) {
		pGame->printMessage("Click on empty cells to add Bomb Bricks  ==> Right-Click to stop <==");
		int x, y;
		clicktype t = pGame->waitMouseClick(x, y);
		while (t == LEFT_CLICK)
		{
			point clicked;
			clicked.x = x;
			clicked.y = y;
			if (y > config.toolBarHeight && y < config.gridHeight + config.toolBarHeight) {
				grid* pGrid = pGame->getGrid();
				pGrid->addBrick(BRK_BMB, clicked);
				pGrid->draw();
			};
			t = pGame->waitMouseClick(x, y);
		}
		pGame->printMessage("");
	}
}

////////////////////////////////////////////////////  class iconSaveLevel   //////////////////////////////////////////////

iconSaveLevel::iconSaveLevel(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconSaveLevel::onClick()
{
	if (pGame->getMode() == MODE_DSIGN) {
		ofstream saveFile("save.txt");
		if (saveFile.is_open())
		{
			for (int i = 0; i < pGame->getGrid()->getrows(); i++)
			{
				for (int j = 0; j < pGame->getGrid()->getcols(); j++)
				{
					if (pGame->getGrid()->getMatrix()[i][j] != NULL)
					{
						saveFile << i << "\t" << j << "\t" << pGame->getGrid()->getMatrix()[i][j]->getType() << endl;
					}
				}
			}
			saveFile.close();

		}
		else
		{
			pGame->printMessage("Error opening save file");
		}
	}
		

}

////////////////////////////////////////////////////  class iconDelBrick   //////////////////////////////////////////////

iconDelBrick::iconDelBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconDelBrick::onClick()
{
	if (pGame->getMode() == MODE_DSIGN) {
		pGame->printMessage("Click on bricks cells to delete  ==> Right-Click to stop <==");
		int x, y;
		clicktype t = pGame->waitMouseClick(x, y);
		while (t == LEFT_CLICK)
		{

			if (y > config.toolBarHeight && y < config.gridHeight + config.toolBarHeight) {

				point clicked;
				clicked.x = x;
				clicked.y = y;
				grid* pGrid = pGame->getGrid();
				if (pGame->getGrid()->getMatrix()[(clicked.y - uprLft.y) / config.brickHeight - 1][clicked.x / config.brickWidth] != NULL) {
					delete pGame->getGrid()->getMatrix()[(clicked.y - uprLft.y) / config.brickHeight - 1][clicked.x / config.brickWidth];
					pGrid->draw();
				};
				t = pGame->waitMouseClick(x, y);
			}
		}
		pGame->printMessage("");
	};

}

////////////////////////////////////////////////////  class iconLoadLevel   //////////////////////////////////////////////

iconLoadLevel::iconLoadLevel(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconLoadLevel::onClick()
{
	if (pGame->getMode() == MODE_DSIGN) {
			ifstream loadFile("save.txt");
			if (loadFile.is_open())
			{
				for (int i = 0; i < pGame->getGrid()->getrows(); i++)
				{
					for (int j = 0; j < pGame->getGrid()->getcols(); j++)
					{
						if (pGame->getGrid()->getMatrix()[i][j] != NULL)
						{
							delete pGame->getGrid()->getMatrix()[i][j];
						}
					}
				}
				pGame->getGrid()->draw();
				int row, col;
				int type;
				while (loadFile >> row >> col >> type)
				{
					point index;
					index.x = col * config.brickWidth;
					index.y = row * config.brickHeight + config.toolBarHeight;
					grid* pGrid = pGame->getGrid();
					pGrid->addBrick((BrickType)type, index);
					pGrid->draw();
				}
				loadFile.close();
			}
			else
			{
				pGame->printMessage("Error opening save file, make sure the ''save.txt'' file is in the game directory");
			}
		}

}
////////////////////////////////////////////////////  class iconPlay   //////////////////////////////////////////////

iconPlay::iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPlay::onClick()
{	
	pGame->setMode(MODE_PLAY);
	//TO DO: add code for cleanup and game exit here

}
////////////////////////////////////////////////////  class iconPause   //////////////////////////////////////////////

iconPause::iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPause::onClick()
{	
	if (pGame->getMode() == MODE_PLAY) {

		//TO DO: add code for cleanup and game exit here
		pGame->setMode(MODE_PAUSE);
	};
}
////////////////////////////////////////////////////  class iconContinue   //////////////////////////////////////////////

iconContinue::iconContinue(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconContinue::onClick()
{
	if (pGame->getMode() == MODE_PAUSE) {

		pGame->setMode(MODE_PLAY);
		//TO DO: add code for cleanup and game exit here
	};

}

////////////////////////////////////////////////////  class iconStop   //////////////////////////////////////////////

iconStop::iconStop(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconStop::onClick()
{
	if (pGame->getMode() == MODE_PAUSE || pGame->getMode() == MODE_PLAY) {

		pGame->setMode(MODE_DSIGN);
		//TO DO: add code for cleanup and game exit here
	};

}


void iconAddNormalBrick::onClick()
{
	if (pGame->getMode() == MODE_DSIGN) {

		pGame->printMessage("Click on empty cells to add Normal Bricks  ==> Right-Click to stop <==");
		int x, y;
		clicktype t = pGame->waitMouseClick(x, y);
		while (t == LEFT_CLICK)
		{
			point clicked;
			clicked.x = x;
			clicked.y = y;
			if (y > config.toolBarHeight && y < config.gridHeight + config.toolBarHeight) {

				grid* pGrid = pGame->getGrid();
				pGrid->addBrick(BRK_NRM, clicked);
				pGrid->draw();
			};
			t = pGame->waitMouseClick(x, y);
		}
		pGame->printMessage("");

	};
}

////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
iconExit::iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconExit::onClick()
{
	

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
	iconsImages[ICON_ADD_HARD] = "images\\ToolbarIcons\\HardBrick.jpg";
	iconsImages[ICON_ADD_ROCK] = "images\\ToolbarIcons\\rock.jpg";
	iconsImages[ICON_ADD_BOMB] = "images\\ToolbarIcons\\bomb.jpg";
	iconsImages[ICON_SAVE] = "images\\ToolbarIcons\\SaveLevel.jpg";
	iconsImages[ICON_DEL] = "images\\ToolbarIcons\\delete.jpg";
	iconsImages[ICON_LOAD] = "images\\ToolbarIcons\\load.jpg";
	iconsImages[ICON_PLAY] = "images\\ToolbarIcons\\PlayIcon.jpg";
	iconsImages[ICON_PAUSE] = "images\\ToolbarIcons\\pause.jpg";
	iconsImages[ICON_CONTINUE] = "images\\ToolbarIcons\\continue.jpg";
	iconsImages[ICON_STOP] = "images\\ToolbarIcons\\stop.jpg";
	iconsImages[ICON_EXIT] = "images\\ToolbarIcons\\exit.jpg";

	point p;
	p.x = 0;
	p.y = 0;

	iconsList = new toolbarIcon * [ICON_COUNT];

	//For each icon in the tool bar
	//	1- Create an object setting its upper left corner, width and height
	iconsList[ICON_ADD_NORM] = new iconAddNormalBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ADD_HARD] = new iconAddHardBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ADD_ROCK] = new iconAddRockBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ADD_BOMB] = new iconAddBombBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_SAVE] = new iconSaveLevel(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_DEL] = new iconDelBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_LOAD] = new iconLoadLevel(p, config.iconWidth, height, pGame);
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
	if (pGame->getMode() == 0){
		pGame->getWind()->DrawRectangle(0, 0, pGame->getWind()->GetWidth(), height);
		for (int i = 0; i < 7; i++)
			iconsList[i]->draw();
		iconsList[ICON_EXIT]->draw();
		iconsList[ICON_PLAY]->draw();
	}
	else if (pGame->getMode() == 1) {
		pGame->getWind()->DrawRectangle(0, 0, pGame->getWind()->GetWidth(), height);
		for (int i = 7; i < ICON_COUNT; i++)
			iconsList[i]->draw();
	}
	window* pWind = pGame->getWind();
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, height, pWind->GetWidth(), height);

}

//handles clicks on toolbar icons, returns true if exit is clicked
bool toolbar::handleClick(int x, int y)
{
	if (x > ICON_COUNT * config.iconWidth)	//click outside toolbar boundaries
		return false;


	//Check which icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();	//execute onClick action of clicked icon

	if (clickedIconIndex == ICON_EXIT) return true;

	return false;


}
