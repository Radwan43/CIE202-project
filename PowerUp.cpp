#include "PowerUp.h"

Power::Power(const point& r_uprleft, game* r_pGame, PowerType type):
    collidable(r_uprleft, config.brickHeight, config.brickHeight, r_pGame)
{
    //put the new 
    this->type = type;
    this->pGame->getWind()->DrawImage("images\\bricks\\NormalBrick.jpg", uprLft.x, uprLft.y, config.brickHeight, config.brickHeight);
    this->draw();


}

void Power::movePower() {
    window* pWin = pGame->getWind();
    grid* pGrid = pGame->getGrid();
    int row, column;
    pWin->SetBrush(config.bkGrndColor);
    pWin->SetPen(config.bkGrndColor, 1);
    pWin->DrawRectangle(uprLft.x , uprLft.y, uprLft.x + config.brickHeight, uprLft.y + config.brickHeight);

    //if (pGame->getGrid()->getMatrix()[(clicked.y - uprLft.y) / config.brickHeight - 1][clicked.x / config.brickWidth] != NULL) {
    //    delete pGame->getGrid()->getMatrix()[(clicked.y - uprLft.y) / config.brickHeight - 1][clicked.x / config.brickWidth];
    //};
    row = (uprLft.y - config.toolBarHeight) / config.brickHeight - 1;
    column = uprLft.x / config.brickWidth;

    if (pGrid->getMatrix()[row][column])
        pGrid->getMatrix()[row][column]->draw();

}