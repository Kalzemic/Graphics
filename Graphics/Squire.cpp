#include "Squire.h"
#include "random"

Squire::Squire(Room room, int color): health(100), ammo(20), health_stock(5)
{
	x = rand() % room.getWidth();
	x += room.getCenterX();
	x -= (room.getWidth() / 2);
	y = rand() % room.getHeight();
	y += room.getCenterY();
	y -= (room.getHeight() / 2);
}
