#pragma once

#include "Config.h"
#include <vector>
#include <typeinfo>

//#include 
class Enemy
{
public:
	double x, y, Vx, Vy;
	int size;	//radius
	enum EnemyType { DIAGONAL, SHOOTINGDIAGONAL, GROUPPER, BLOCKER };

	static std::vector<Enemy *> enemyList;


	template <class T>
	static std::vector<Enemy *> GetInst() {

		std::vector<Enemy *> aux;
		
		for (int i = 0; i < enemyList.size(); i++) {
			std::cout << "X";

			if (auto sp = dynamic_cast<T*>(enemyList[i])) {
				
				aux.push_back(enemyList[i]);
			}
		}

		return aux;
	}
	

	template <class T, class T2, class...Rest>
	static std::vector<Enemy *> GetInst() {

		std::vector<Enemy *> aux;

		for (int i = 0; i < enemyList.size(); i++) {
			std::cout << "X";

			if (auto sp = dynamic_cast<T*>(enemyList[i])) {

				aux.push_back(enemyList[i]);
		}
			}

		std::vector<Enemy *> aux2 = GetInst<T2, Rest...>();
		aux.insert(aux.end(), aux2.begin(), aux2.end());
		return(aux);
	}
	


	void Move(float timeStep) {}
	void Act() {}
	
	

protected:
	
	Enemy(int x = 0, int dirX = 1) : x(x), y(0), Vy(ENEMY_SPEED), size(ENEMY_SIZE) {
		if (dirX > 0)
			Vx = ENEMY_SPEED;
		else
			Vx = -ENEMY_SPEED;
		enemyList.push_back(this);
	}

	virtual ~Enemy();
};

class EnemyDiagonal : public Enemy {
public:
	EnemyDiagonal(int x = 0, int dirX = 1) : Enemy(x, dirX) {}
	//void Move(float timeStep);
	//void Act();


};

class EnemyShooting : public Enemy {
public:
	EnemyShooting(int x = 0, int dirX = 1) : Enemy(x, dirX) {}
	//~EnemyShooting();
	//void Move(float timeStep);
	//void Act();

};

class EnemyGroupper : Enemy {
public:


};

class EnemyBlocker : Enemy {
public:

};
