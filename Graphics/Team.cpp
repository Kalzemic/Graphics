#include "Team.h"

Team::Team(Room room, const int color) : color(color) {
    fighters[0] = std::make_unique<Fighter>(room, color);
    fighters[1] = std::make_unique<Fighter>(room, color);
    squire = std::make_unique<Squire>(room, color);
}

void Team::TakeTurn(int board[MSZ][MSZ],Team* enemy, std::vector<std::unique_ptr<Bullet>>& bullets)
{
    fighters[0]->Action(board,enemy->fighters, bullets);
    fighters[1]->Action(board,enemy->fighters, bullets);
}