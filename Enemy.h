#pragma once

#include "Config.h"
#include "Missile.h"
#include "GameField.h"
#include <vector>
#include <typeinfo>

//#include 
class Enemy
{
public:
	double x, y, Vx, Vy;
	int size;	//radius
	double bounceY; //Where to  bounce off at Y axis
	enum EnemyType { DIAGONAL, SHOOTINGDIAGONAL, GROUPPER, BLOCKER } enemyType;

	Colour colour;

	static std::vector<Enemy *> enemyList;


	template <class T>
	static std::vector<Enemy *> GetInst() {

		std::vector<Enemy *> aux;
		
		for (int i = 0; i < enemyList.size(); i++) {

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

			if (auto sp = dynamic_cast<T*>(enemyList[i])) {

				aux.push_back(enemyList[i]);
			}
		}

		std::vector<Enemy *> aux2 = GetInst<T2, Rest...>();
		aux.insert(aux.end(), aux2.begin(), aux2.end());
		return(aux);
	}
	


	virtual void Move(float timeStep);

	static void MoveAll(float timeStep);

	virtual void Act() {}
	
	virtual ~Enemy();

protected:
	
	Enemy(int x = 0, int dirX = 1) : x(x), y(0), Vy(ENEMY_SPEED/10), size(ENEMY_SIZE), bounceY(0) {
		if (dirX > 0)
			Vx = ENEMY_SPEED;
		else
			Vx = -ENEMY_SPEED;
		enemyList.push_back(this);
	}

	
};

class EnemyDiagonal : public Enemy {
public:
	EnemyDiagonal(int x = 0, int dirX = 1) : Enemy(x, dirX) {
															enemyType = DIAGONAL;
															colour = { 255, 255, 0, 255 };
															}
	void Move(float);


};

class EnemyShooting : public EnemyDiagonal {
public:
	EnemyShooting(int x = 0, int dirX = 1) : EnemyDiagonal(x, dirX) { 
																	enemyType = SHOOTINGDIAGONAL; 
																	colour = { 255, 0, 0, 255 };
																	}
	EnemyShooting(Enemy&);

	void Act();

};

class EnemyGroupper : public Enemy {
public:
	EnemyGroupper(int x = 0, int dirX = 1) : Enemy(x, dirX) {
															enemyType = GROUPPER;
															colour = { 0, 255, 125, 255 };
															}
	void Act();

};

class EnemyBlocker : public Enemy {
public:
	EnemyBlocker(int x = 0, int dirX = 1) : Enemy(x, dirX) {
															enemyType = BLOCKER;
															colour = { 255, 0, 255, 255 };
															}
	void Act();
};
