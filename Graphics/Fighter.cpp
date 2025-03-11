#include "Fighter.h"
#include "random"
#include <stack>
Fighter::Fighter(Room room, const int color) : health(100), ammo(10), character(std::rand() % 3), color(color)
{
	x = rand() % room.getWidth();
	x += room.getCenterX();
	x -= (room.getWidth() / 2);
	y = rand() % room.getHeight();
	y += room.getCenterY();
	y -= (room.getHeight() / 2);
}


Cell* Fighter::SearchEnemy(int board[MSZ][MSZ])
{
	std::stack<Cell*> cells;
	cells.push(new Cell(y, x, NULL));
	while (board[cells.top()->getRow()][cells.top()->getCol()]==500-color)
	{
		Cell* current = cells.top();
		cells.pop();
		if (board[current->getRow() + 1][current->getCol()] == SPACE)
			cells.push(new Cell(current->getRow() + 1, current->getCol(), current));
		if (board[current->getRow() - 1][current->getCol()] == SPACE)
			cells.push(new Cell(current->getRow() - 1, current->getCol(), current));
		if (board[current->getRow()][current->getCol()+1] == SPACE)
			cells.push(new Cell(current->getRow() , current->getCol()+1, current));
		if (board[current->getRow()][current->getCol()-1] == SPACE)
			cells.push(new Cell(current->getRow() , current->getCol()-1, current));
	}
	Cell* target = cells.top();
	cells.pop();
	while (!cells.empty())
	{
		Cell* current = cells.top();
		cells.pop();
		delete current;
	}
}