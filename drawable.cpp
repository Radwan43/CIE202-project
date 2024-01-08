#include "drawable.h"
#include "game.h"
#include <iostream>

drawable::drawable(point r_uprleft, int r_width, int r_height, game* r_pGame)
    : drawType(DRAW_IMAGE), uprLft(r_uprleft), width(r_width), height(r_height), pGame(r_pGame) {}

drawable::drawable(point r_uprleft, int r_width, int r_height, game* r_pGame, const string& shapeType)
    : drawType(DRAW_SHAPE), shapeType(shapeType), uprLft(r_uprleft), width(r_width), height(r_height), pGame(r_pGame) {}

void drawable::draw() const
{

    // Draw image or shape based on the drawType
    window* pWind = pGame->getWind();
    if (drawType == DRAW_IMAGE) {
        pWind->DrawImage(imageName, uprLft.x, uprLft.y, width, height);
    }
    else if (drawType == DRAW_SHAPE) {
        // Drawing logic for shapes
        if (shapeType == "circle") {
            pWind->SetPen(0.5, 0.1, 0.9, 0);
            pWind->SetBrush(0.5, 0.1, 0.9);
            pWind->DrawCircle(uprLft.x + width / 2, uprLft.y + height / 2, width / 2);
        }
        else {
            // Handle drawing logic for other shapes if needed
        }
    }
}

void drawable::setImageName(const string& path)
{
        imageName = path;
    
}
