#include "drawable.h"
#include "game.h"

drawable::drawable(point r_uprlft, int r_width, int r_height, game* r_pGame)
{
	uprLft = r_uprlft;
	width = r_width;
	height = r_height;
	pGame = r_pGame;
}

void drawable::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(imageName, uprLft.x, uprLft.y, width, height);
}

void drawable::setImageName(string path)
{
	imageName = path;
}




