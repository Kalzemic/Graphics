#include "Fighter.h"
#include "Bullet.h"
#include "Cell.h"
#include "CompareCells.h"
#include "random"
#include <stack>
#include <queue>
#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <memory>
#include <unordered_map>


Fighter::Fighter(Room room, const int color) : health(100), ammo(10), character(std::rand() % 3), color(color), state(FighterState::IDLE)
{
    x = rand() % room.getWidth();
    x += room.getCenterX();
    x -= (room.getWidth() / 2);
    y = rand() % room.getHeight();
    y += room.getCenterY();
    y -= (room.getHeight() / 2);
}

bool Fighter::HasLineOfSight(int board[MSZ][MSZ], Cell* target)
{
    if (!target) return false;
    int targetX = target->getCol();
    int targetY = target->getRow();

    if (x == targetX) // Vertical check
    {
        int start = std::min(y, targetY);
        int end = std::max(y, targetY);
        for (int i = start + 1; i < end; i++)
        {
            if (board[i][x] == WALL)
                return false;
        }
        return true;
    }
    else if (y == targetY) // Horizontal check
    {
        int start = std::min(x, targetX);
        int end = std::max(x, targetX);
        for (int i = start + 1; i < end; i++)
        {
            if (board[y][i] == WALL)
                return false;
        }
        return true;
    }
    return false;
}

Cell* Fighter::Search(int board[MSZ][MSZ], int targetColor)
{
    std::priority_queue<Cell*, std::vector<Cell*>, CompareCells> pq;
    std::unordered_map<int, std::unordered_map<int, Cell*>> visited;

    pq.push(new Cell(y, x, -1, -1, 0, nullptr));

    while (!pq.empty())
    {
        Cell* current = pq.top();
        pq.pop();

        int row = current->getRow();
        int col = current->getCol();

        if (board[row][col] == targetColor) // Found enemy
        {
            while (current->getParent() && current->getParent()->getParent()) // Find next move
            {
                current = current->getParent();
            }
            return new Cell(current->getRow(), current->getCol(), nullptr); // Return next step
        }

        std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        for (auto& dir : directions)
        {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            if (board[newRow][newCol] == SPACE || board[newRow][newCol] == targetColor)
            {
                if (visited[newRow][newCol] == nullptr) // Only add if not already visited
                {
                    Cell* nextCell = new Cell(newRow, newCol, -1, -1, 0, current);
                    pq.push(nextCell);
                    visited[newRow][newCol] = nextCell;
                }
            }
        }
    }

    return nullptr; // No valid move found
}

void Fighter::Move(int board[MSZ][MSZ], Cell* nextStep)
{
    if (!nextStep) return; // No valid move

    board[y][x] = SPACE; // Clear old position
    y = nextStep->getRow();
    x = nextStep->getCol();
    board[y][x] = color; // Update fighter position

    delete nextStep; // Free memory to prevent leaks
}



void Fighter::Shoot(std::vector<std::unique_ptr<Bullet>>& bullets, Fighter& target)
{
    if (ammo > 0)
    {
        ammo--;
        double angle = atan2(target.getY() - y, target.getX() - x);
        bullets.push_back(std::make_unique<Bullet>(x, y, angle));
    }
}

void Fighter::Action(int board[MSZ][MSZ], std::array<std::unique_ptr<Fighter>, 2>& fighters, std::vector<std::unique_ptr<Bullet>>& bullets)
{
    if (health <= 0)
    {
        state = FighterState::DEAD;
        board[y][x] = SPACE; // Remove fighter from the board
        return;
    }

    Cell* targetCell = Search(board, 500 - color);

    switch (state)
    {
    case FighterState::IDLE:
        state = FighterState::MOVING;
        break;

    case FighterState::MOVING:
        if (targetCell)
        {
            Move(board, targetCell); // Move() now deletes the cell
            if (HasLineOfSight(board, targetCell))
                state = FighterState::ATTACKING;
        }
        break;

    case FighterState::ATTACKING:
        if (targetCell && HasLineOfSight(board, targetCell))
        {
            for (auto& enemy : fighters)
            {
                if (enemy->getX() == targetCell->getCol() && enemy->getY() == targetCell->getRow())
                {
                    Shoot(bullets, *enemy);
                    break;
                }
            }
        }
        state = FighterState::MOVING;
        break;

    case FighterState::DEAD:
        return; // Do nothing
    }
}

