#include "Bullet.h"
#include <math.h>
#include "glut.h"

// angle is in radians
Bullet::Bullet(double xx, double yy, double angle)
{
	x = xx;
	y = yy;
	dir_angle = angle;
	dirX = cos(angle);
	dirY = sin(angle);
	speed = 0.3;
	isMoving = true;;
}



void Bullet::show()
{
	glColor3d(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y);
	glVertex2d(x , y+ 0.5);
	glVertex2d(x + 0.5, y);
	glVertex2d(x , y- 0.5);
	glEnd();
}

void Bullet::SimulateExplosion(int maze[MSZ][MSZ], double sm[MSZ][MSZ])
{
	isMoving = true;
	while (isMoving)
	{
		sm[(int)y][(int)x] += SECURITY_FACTOR;
		move(maze);
	}
}

void Bullet::move(int maze[MSZ][MSZ])
{
    if (state == BulletState::MOVING)
    {
        // Clear previous position
        if (maze[(int)y][(int)x] == BULLET)
            maze[(int)y][(int)x] = SPACE;

        // Move bullet
        x += speed * dirX;
        y += speed * dirY;

        // Check collision
        if (maze[(int)y][(int)x] == WALL)
        {
            state = BulletState::HIT;
            isMoving = false;
        }
        else
        {
            maze[(int)y][(int)x] = BULLET;
        }
    }
}

void Bullet::Update(int board[MSZ][MSZ])
{
    switch (state)
    {
    case BulletState::MOVING:
        move(board);
        break;

    case BulletState::HIT:
        isMoving = false;
        break;
    }
}

