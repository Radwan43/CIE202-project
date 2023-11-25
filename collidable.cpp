#include "collidable.h"

collidable::collidable(point r_uprleft, int r_width, int r_height, game* r_pGame):
			drawable(r_uprleft, r_width, r_height,  r_pGame)
{

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

	if (((point1.y >= point2.y - height2) && (point1.y <= point2.y + height1)) && ((point1.x == point2.x + width2) || (point1.x == point2.x - width1))) {
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
	else if (((point1.x >= point2.x - width1) && (point1.x <= point2.x + width2)) && ((point1.y == point2.y - height2) || (point1.y == point2.y + height1))) {

		if (point1.y == point2.y - height2) { CollisionPoint.y = point1.y; }
		else { CollisionPoint.y = point2.y; };

		if (point1.x > point2.x) {
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