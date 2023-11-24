#pragma once
#include <string>
using namespace std;
#include "CMUgraphicsLib\CMUgraphics.h"

class game;     //forward declaration

struct point
{
int x, y;
};

//Base class for any drawable object in the game including bricks, ball, toolbar icons,... etc
//Each drawable object is bounded by a rectangular boundary
class drawable
{
protected:
	string imageName;	//path to its image
    point uprLft;       //upper left corner of the drawable object
    int width, height;  

protected:
    game* pGame;        //pointer to game object
public:
    drawable(point r_uprleft, int r_width, int r_height, game* r_pGame);
    virtual void draw() const;//for a drwable object to draw itself on the screen
	void setImageName(string path);
};




