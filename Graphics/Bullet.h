#pragma once
#include "definitions.h"


enum class BulletState { INACTIVE, MOVING, HIT };


class Bullet
{
private: 
	double x, y;
	double dir_angle;
	double dirX, dirY;
	double speed;
	bool isMoving;
	BulletState state;
public:
	Bullet(double xx, double yy, double angle);
	double getY() { return y; }
	double getX() { return x; }
	void move(int maze[MSZ][MSZ]);
	void show();
	void setIsMoving(bool value) { isMoving = value; }
	void SimulateExplosion(int maze[MSZ][MSZ], double sm[MSZ][MSZ]);
	void Update(int board[MSZ][MSZ]);

};

