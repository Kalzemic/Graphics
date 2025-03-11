#pragma once
#include "Room.h"



class Squire
{
private: 
	int health; 
	int ammo;
	int x;
	int y;
	int health_stock;
public:
	Squire(Room room, int color);
	~Squire() {}
	int getHealth() { return health; }
	int getAmmo() { return ammo; }
	int getX() { return x; }
	int getY() { return y; }
};

