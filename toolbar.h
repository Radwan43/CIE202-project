#pragma once

//This file contains all classes related to toolbar (toolbar icon classes & toolbar class itself)
#include "drawable.h"

////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
//Base class for all toolbar icons 
class toolbarIcon :public drawable
{
public:
	toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick() = 0;   //The action that should be taken when this icon is clicked
};

////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
class iconAddNormalBrick :public toolbarIcon
{
public:
	iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconAddHardBrick   //////////////////////////////////////////////
class iconAddHardBrick :public toolbarIcon
{
public:
	iconAddHardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconAddRockBrick   //////////////////////////////////////////////
class iconAddRockBrick :public toolbarIcon
{
public:
	iconAddRockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconAddBombBrick   //////////////////////////////////////////////
class iconAddBombBrick :public toolbarIcon
{
public:
	iconAddBombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconAddLifeBrick   //////////////////////////////////////////////
class iconAddLifeBrick :public toolbarIcon
{
public:
	iconAddLifeBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

//////////////////////////////////////////////////////  class iconSaveLevel   //////////////////////////////////////////////
class iconSaveLevel :public toolbarIcon
{
public:
	iconSaveLevel(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};


//////////////////////////////////////////////////////  class iconLoadLevel   //////////////////////////////////////////////
class iconLoadLevel :public toolbarIcon
{
public:
	iconLoadLevel(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

//////////////////////////////////////////////////////  class iconiconDelBrick   //////////////////////////////////////////////
class iconDelBrick :public toolbarIcon
{
public:
	iconDelBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

//////////////////////////////////////////////////////  class iconPlay   //////////////////////////////////////////////
class iconPlay :public toolbarIcon
{
public:
	iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
//////////////////////////////////////////////////////  class iconPause   //////////////////////////////////////////////
class iconPause :public toolbarIcon
{
public:
	iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
//////////////////////////////////////////////////////  class iconContinue   //////////////////////////////////////////////
class iconContinue :public toolbarIcon
{
public:
	iconContinue(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

//////////////////////////////////////////////////////  class iconStop   //////////////////////////////////////////////
class iconStop :public toolbarIcon
{
public:
	iconStop(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
class iconExit :public toolbarIcon
{
public:
	iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
class toolbar :public drawable
{

	enum ICONS //The icons of the toolbar (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_ADD_NORM,	//add normal brick
		ICON_ADD_HARD,	//add hard brick
		ICON_ADD_ROCK,	//add rock brick
		ICON_ADD_BOMB,	//add bomb brick
		ICON_ADD_LIFE,	//add bomb brick

		//TODO: Add more icons names here

		ICON_SAVE,
		
		ICON_DEL,
		ICON_LOAD,
		ICON_PLAY,
		ICON_PAUSE,
		ICON_CONTINUE,
		ICON_STOP,

		ICON_EXIT,		//Exit icon

		ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};

private:
	toolbarIcon** iconsList; //an array of toolbarIcon pointers
	string iconsImages[ICON_COUNT];
	game* pGame;

public:
	toolbar(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~toolbar();
	void draw() const;
	bool handleClick(int x, int y);	//handles clicks on toolbar icons, returns true if exit is clicked
};

