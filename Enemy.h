#pragma once

#include <vector>

//#include 
class Enemy
{
public:
	double x, y, Vx, Vy;
	int width, height;

	
private:
	Enemy();
	~Enemy();
	static std::vector<Enemy *> enemyList;
	void Move(float timeStep);
	void Act();
};

class EnemyDiagonal : Enemy {
public:
	EnemyDiagonal(int x = 0, int dir = 0);
	~EnemyDiagonal();
	void Move(float timeStep);
	void Act();

};

class EnemyShooting : Enemy {
public:
	EnemyShooting(int x = 0, int dir = 0);
	~EnemyShooting();
	void Move(float timeStep);
	void Act();

};
