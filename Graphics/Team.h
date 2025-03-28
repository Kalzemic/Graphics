#pragma once

#include <array>
#include "Room.h"
#include "Fighter.h"
#include "Squire.h"
#include <memory>


class Team
{
private: 
	std::array<std::unique_ptr<Fighter>, 2> fighters;
	std::unique_ptr<Squire> squire;
	const int color;
public: 
	Team(Room room, const int color);
	~Team() { }
	void TakeTurn(int board[MSZ][MSZ], Team* enemy, std::vector<std::unique_ptr<Bullet>>& bullets);
	int getColor() { return color; }
	std::array<std::unique_ptr<Fighter>, 2>& getFighters() { return fighters; }
	std::unique_ptr<Squire>& getSquire() { return squire; }
};


