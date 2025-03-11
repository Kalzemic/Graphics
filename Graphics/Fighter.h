#pragma once
#include "Cell.h"
#include "Room.h"

const int AGGRESSIVE = 0;
const int SAFE = 1;
const int STOCKED = 2;
class Fighter
{
private:
	int x;
	int y;
	int color;
	int ammo;
	int health;
	int character;
public:
	Fighter(Room room, const int color);
	~Fighter() {}


	//Getters
	bool enemySpotted;
	int getX() { return x; }
	int getY() { return y; }
	bool isLowAmmo() { return ammo < 4; }
	bool isDamaged() { return health < 50; }

	Cell* SearchEnemy(int board[MSZ][MSZ]);
};


