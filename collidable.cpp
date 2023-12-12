#include "collidable.h"

collidable::collidable(point r_uprleft, int r_width, int r_height, game* r_pGame) :
    drawable(r_uprleft, r_width, r_height, r_pGame)
{
}

collidable::collidable(point r_uprleft, int r_width, int r_height, game* r_pGame, const string& shapeType) :
    drawable(r_uprleft, r_width, r_height, r_pGame, shapeType)
{
}


bool collidable::is_collided(int u1, int u2, int v1, int v2, int width1, int width2, int height1, int height2) {
	if ((is_onLine(u1, u2, width2) || is_onLine(u2, u1, width1)) && (is_inRange(v1, v2, height1, height2))) {
		return true;
	}
	else { return 0; };
}

bool collidable::is_onLine(int u1, int u2, int distance2) {
	return (u1 == u2 + distance2);
}

bool collidable::is_inRange(int v1, int v2, int distance1, int distance2) {
	return ((v1 >= v2 - distance2) && (v1 <= v2 + distance1));
}

point collidable::CheckCollision(collidable* object1, collidable* object2) {
	point& point1 = object1->uprLft;
	point& point2 = object2->uprLft;
	int& width1 = object1->width;
	int& width2 = object2->width;
	int& height1 = object1->height;
	int& height2 = object2->height;



	point CollisionPoint;
	CollisionPoint.x = 0;
	CollisionPoint.y = 0;

	if (is_collided(point1.x, point2.x, point1.y, point2.y, width1, width2, height1, height2)) { //collision on horizontal
		if (point1.x == point2.x + width2) { CollisionPoint.x = point1.x; }
		else { CollisionPoint.x = point2.x; };
		if (point1.y > point2.y) {
			if (point1.y - height1 > point2.y - height2) {
				CollisionPoint.y = (point2.y + (point1.y - height1)) / 2;
			}
			else { CollisionPoint.y = point2.y - height2 / 2; }
		}


		else if (point1.y < point2.y) {
			if (point2.y - height2 > point1.y - height1) {
				CollisionPoint.y = (point1.y + (point2.y - height2)) / 2;
			}
			else { CollisionPoint.y = point1.y - height1 / 2; }
		}

	}
	else if (is_collided(point1.y, point2.y, point1.x, point2.x, -height1, -height2, width2, width1)) { //collision on vertical

		if (point1.y == point2.y - height2) { CollisionPoint.y = point1.y; }
		else { CollisionPoint.y = point2.y; };

		if (point1.x >= point2.x) {
			if (point1.x + width1 > point2.x + width2) {
				CollisionPoint.x = (point1.x + (point2.x + width2)) / 2;
			}
			else { CollisionPoint.x = point1.x + width1 / 2; }
		}


		else if (point1.x < point2.x) {
			if (point2.x + width2 > point1.x + width1) {
				CollisionPoint.x = (point2.x + (point1.x + width1)) / 2;
			}
			else { CollisionPoint.x = point2.x + width2 / 2; }
		}
	}

	return CollisionPoint;
}




// 1- Ball - Platform 
// 2- collision physics

// 3- Powerups, different brick types
// 4- Polishing 
