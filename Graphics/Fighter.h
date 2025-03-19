#ifndef FIGHTER_H
#define FIGHTER_H

#include "Room.h"
#include "Cell.h"
#include "Bullet.h"
#include <memory>
#include <array>
#include "Bullet.h"
#include <memory>
#include <vector>


enum FighterState{MOVING, ATTACKING, IDLE, DEAD};

class Fighter {
private:
    int x, y;
    int health;
    int ammo;
    int character;
    int color;
    FighterState state;

public:
    Fighter(Room room, const int color);

    bool HasLineOfSight(int board[MSZ][MSZ], Cell* target);
    Cell* Search(int board[MSZ][MSZ], int targetColor);
    void Attack(int board[MSZ][MSZ], std::array<std::unique_ptr<Fighter>,2>& fighters, std::vector<std::unique_ptr<Bullet>>& bullets);
    void Action(int board[MSZ][MSZ], std::array<std::unique_ptr<Fighter>, 2>& fighters,std::vector<std::unique_ptr<Bullet>>& bullets);
    void Move(int board[MSZ][MSZ], Cell* target);
    void Shoot(std::vector<std::unique_ptr<Bullet>>& bullets, Fighter& target);
    


    // Getters for position (optional if needed externally)
    int getX() const { return x; }
    int getY() const { return y; }
};

#endif // FIGHTER_H

