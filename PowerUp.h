#pragma once
#include "collidable.h"
#include "Bricks.h"
#include "game.h"
#include "GameTimer.h"

class brick;
class PowerUp : public collidable
{
private:
	bool isActivated = false;

	int powerUpStartTime;
	bool powerUpActive = false;
	int activePowerUp = 0;
	GameTimer* gameTimer;

public:
	PowerUp(const point& r_uprleft, game* r_pGame);

	void collisionAction() override;

	void disable(GameTimer* gameTimer);

	void revertPowerUp();

	void movePowerUp();

	void activatePowerUp();
	bool isActivatedPowerUp();
};
