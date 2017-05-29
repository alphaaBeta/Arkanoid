#pragma once

#include "Config.h"
#include <vector>

//#include 
class Enemy
{
public:
	double x, y, Vx, Vy;
	int width, height;
	enum EnemyType { DIAGONAL, SHOOTINGDIAGONAL, GROUPPER, BLOCKER };
	EnemyType EnemyType;

	static std::vector<Enemy *> enemyList;


	template <class T>
	std::vector<Enemy *> GetInst(T t) {
		std::vector<Enemy *> aux;
		for (int i = 0; i < enemyList.size(); i++) {
			if (enemyList[i]->EnemyType == T.EnemyType) {
				aux.push_back();
			}
		}

		return aux;
	}

	template <class T, class...Rest>
	std::vector<Enemy *> GetInst(T t, Rest...rest) {
		std::vector<Enemy *> aux;
		for (int i = 0; i < enemyList.size(); i++) {
			if (enemyList[i]->EnemyType == T.EnemyType) {
				aux.push_back();
			}
		}
		aux2 = GetInst(rest...);
		return(aux.insert(aux.end(), aux2.begin(), aux2.end());

	}


	void Move(float timeStep) {}
	void Act() {}
	
protected:
	Enemy(int x = 0, int dirX = 1) : x(x), y(0), Vy(ENEMY_SPEED) {
		if (dirX > 0)
			Vx = ENEMY_SPEED;
		else
			Vx = -ENEMY_SPEED;
	}
	~Enemy();
};

class EnemyDiagonal : Enemy {
public:
	EnemyDiagonal(int x = 0, int dirX = 1) : Enemy(x, dirX) { EnemyType = DIAGONAL; }
	void Move(float timeStep);
	void Act();

};

class EnemyShooting : EnemyDiagonal, public Enemy {
public:
	EnemyShooting(int x = 0, int dirX = 1) : EnemyDiagonal(x, dirX) { Enemy::EnemyType = SHOOTINGDIAGONAL; }
	//~EnemyShooting();
	//void Move(float timeStep);
	void Act();

};

class EnemyGroupper : Enemy {
public:


};

class EnemyBlocker : Enemy {
public:

};
