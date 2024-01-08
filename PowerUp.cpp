#include "PowerUp.h"
#include "game.h"
#include "grid.h"
#include <iostream>
#include "paddle.h";
#include <random>
#
PowerUp::PowerUp(const point& r_uprleft, game* r_pGame) :
    collidable(r_uprleft, config.brickHeight, config.brickHeight, r_pGame)
{
    imageName = "images\\bricks\\NormalBrick.jpg";

}

void PowerUp::collisionAction()
{

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(1, 6);

    int random_number = dis(gen);

    if (random_number == 1) {
        pGame->getWind()->SetPen(LAVENDER, 1);
        pGame->getWind()->SetBrush(LAVENDER);
        pGame->getWind()->DrawRectangle(pGame->getPaddle()->getUpperLeft().x, pGame->getPaddle()->getUpperLeft().y
            , pGame->getPaddle()->getUpperLeft().x + pGame->getPaddle()->getWidth(), pGame->getPaddle()->getUpperLeft().y + 20);

        pGame->getPaddle()->setWidth(75);

    }
    else if (random_number == 2) {
        pGame->getPaddle()->setWidth(150);
    }
    else if (random_number == 3) {
		pGame->getPaddle()->setInverted(true);
    }
    else if (random_number == 4) {
        pGame->getBall()->setAttatched(true);
        pGame->getBall()->set_motion(false);
        pGame->getBall()->setTrajectory(pGame->getBall()->getPI() / 2);
    }
    else if (random_number == 5) {
        pGame->getPaddle()->setSpeed(5);
    }
    else if (random_number == 6) {
        pGame->getPaddle()->setSpeed(15);
    }

    if (random_number >= 1 && random_number <= 6) {
        powerUpStartTime = std::stoi(gameTimer->getElapsedTimeString()); // Assuming getElapsedTimeString returns time in seconds as a string
        powerUpActive = true;
        activePowerUp = random_number;
    }

}

void PowerUp::disable(GameTimer* gameTimerr) {
    gameTimer = gameTimerr;
    if (powerUpActive) {
        int currentTime = std::stoi(gameTimer->getElapsedTimeString());
        int elapsedTime = currentTime - powerUpStartTime;

        if (elapsedTime >= 60) {
            revertPowerUp();
            powerUpActive = false;
        }
    }
}

void PowerUp::revertPowerUp() {
    if (activePowerUp == 1) {
		pGame->getPaddle()->setWidth(100);
	}
    else if (activePowerUp == 2) {
		pGame->getPaddle()->setWidth(100);
	}
    else if (activePowerUp == 3) {
		pGame->getPaddle()->setInverted(false);
	}
    else if (activePowerUp == 5) {
		pGame->getPaddle()->setSpeed(10);
	}
    else if (activePowerUp == 6) {
		pGame->getPaddle()->setSpeed(10);
    }
}


void PowerUp::movePowerUp() {

    window* pWin = this->pGame->getWind();
    grid* pGrid = pGame->getGrid();
    int row, column;
    pWin->SetBrush(config.bkGrndColor);
    pWin->SetPen(config.bkGrndColor, 1);
    pWin->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + config.brickHeight, uprLft.y + config.brickHeight);


    row = (uprLft.y - config.toolBarHeight) / config.brickHeight - 1;
    column = uprLft.x / config.brickWidth;
    if (uprLft.y > config.toolBarHeight && uprLft.y < config.gridHeight + config.toolBarHeight) {

        if (pGrid->getMatrix()[row][column])
            pGrid->getMatrix()[row][column]->draw();
        if (row + 1 < pGrid->getrows()) {

            if (pGrid->getMatrix()[row + 1][column])
                pGrid->getMatrix()[row + 1][column]->draw();
        };
    };
    uprLft.y = uprLft.y + 3;
    this->draw();

    if (uprLft.y > 520) {
        pWin->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + config.brickHeight, uprLft.y + config.brickHeight);
    }

}

void PowerUp::activatePowerUp() {
    isActivated = true;
}

bool PowerUp::isActivatedPowerUp() {
    return isActivated;
}

