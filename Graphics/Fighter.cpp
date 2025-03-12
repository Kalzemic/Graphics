#include "Fighter.h"
#include "random"
#include <stack>
#include <queue>
Fighter::Fighter(Room room, const int color) : health(100), ammo(10), character(std::rand() % 3), color(color)
{
	x = rand() % room.getWidth();
	x += room.getCenterX();
	x -= (room.getWidth() / 2);
	y = rand() % room.getHeight();
	y += room.getCenterY();
	y -= (room.getHeight() / 2);
}

void Fighter::Attack(int board[MSZ][MSZ])
{
	Cell* target = Search(board, 500-color);
		if (target->getRow() == y)
		{
			for (int i = std::min(x, target->getCol()); i < std::max(x, target->getCol());i++)
			{
				if (board[y][i] == WALL)
				{
					Move(board, target);
					delete target;
					return;
				}
			}
			///shoot

			return;
		}
		if (target->getCol() == x)
		{
			for (int i = std::min(y, target->getRow()); i < std::max(y, target->getRow());i++)
			{
				if (board[i][x] == WALL)
				{
					Move(board, target);
					delete target;
					return;
				}
			}
			///shoot
			return;
		}
		Move(board,target);
		delete target;
		return;

}


Cell* Fighter::Search(int board[MSZ][MSZ], int targetcolor)
{
	std::queue<Cell*> cells;
	cells.push(new Cell(y, x, NULL));
	while (!cells.empty())
	{
		Cell* current = cells.front();
		cells.pop();
		if (board[current->getRow()][current->getCol()] == targetcolor)
		{
			Cell* targetcell = current;
			while (!cells.empty())
			{
				Cell* temp = cells.front();
				cells.pop();
				delete temp;
			}
			for (int i = 0;i < MSZ;i++)
			{
				for (int j = 0;j < MSZ;j++)
				{
					if (board[i][j] == BLACK)
						board[i][j] = SPACE;
				}
			}
			return targetcell;
		}
		
		if (board[current->getRow() + 1][current->getCol()] == SPACE || board[current->getRow() + 1][current->getCol()] == targetcolor)
		{
			cells.push(new Cell(current->getRow() + 1, current->getCol(), current));
			if(board[current->getRow() + 1][current->getCol()] == SPACE)
				board[current->getRow() + 1][current->getCol()] = BLACK;
		}
		if (board[current->getRow() - 1][current->getCol()] == SPACE || board[current->getRow() - 1][current->getCol()] == targetcolor)
		{
			cells.push(new Cell(current->getRow() - 1, current->getCol(), current));
			if(board[current->getRow() - 1][current->getCol()] == SPACE)
				board[current->getRow() - 1][current->getCol()] = BLACK;
		}
		if (board[current->getRow()][current->getCol() + 1] == SPACE || board[current->getRow() ][current->getCol()+1] == targetcolor)
		{
			cells.push(new Cell(current->getRow(), current->getCol() + 1, current));
			if(board[current->getRow() ][current->getCol()+1] == SPACE)
				board[current->getRow() ][current->getCol()+1] = BLACK;
		}
		if (board[current->getRow()][current->getCol() - 1] == SPACE || board[current->getRow()][current->getCol()-1] == targetcolor)
		{
			cells.push(new Cell(current->getRow(), current->getCol() - 1, current));
			if(board[current->getRow() ][current->getCol()-1] == SPACE)
				board[current->getRow() ][current->getCol()-1] = BLACK;
		}
		delete current;
	}
	return nullptr; // Return nullptr if no target is found
}


void Fighter::Move(int board[MSZ][MSZ], Cell* target)
{
	Cell up(y + 1, x, target->getRow(), target->getCol(), 0, NULL);
	Cell down(y - 1, x, target->getRow(), target->getCol(), 0, NULL);
	Cell right(y, x + 1, target->getRow(), target->getCol(), 0, NULL);
	Cell left(y, x - 1, target->getRow(), target->getCol(), 0, NULL);

	int upcolor = board[up.getRow()][up.getCol()];
	int downcolor = board[down.getRow()][down.getCol()];
	int rightcolor = board[right.getRow()][right.getCol()];
	int leftcolor = board[left.getRow()][left.getCol()];

	std::vector<std::pair<Cell, int>> cells = {
		{up, upcolor},
		{down, downcolor},
		{right, rightcolor},
		{left, leftcolor}
	};

	// Sort cells by their heuristic value (H)
	std::sort(cells.begin(), cells.end(), [](const std::pair<Cell, int>& a, const std::pair<Cell, int>& b) {
		Cell cell1 = a.first;
		Cell cell2 = b.first;
		return cell1.getH() < cell2.getH();
		});

	board[y][x] = SPACE;

	for (const auto& cell : cells)
	{
		if (cell.second == SPACE)
		{
			Cell temp = cell.first;
			y = temp.getRow();
			x = temp.getCol();
			break;
		}
	}

	board[y][x] = color;
}


void Fighter::Action(int board[MSZ][MSZ])
{
	Attack(board);
}