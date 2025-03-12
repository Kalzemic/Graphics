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
	int getX() { return x; }
	int getY() { return y; }
	bool isLowAmmo() { return ammo < 4; }
	bool isDamaged() { return health < 50; }

	Cell* Search(int board[MSZ][MSZ], int targetcolor);
	void Action(int board[MSZ][MSZ]);
	void Attack(int board[MSZ][MSZ]);
	void Move(int board[MSZ][MSZ],Cell* target);
};


