#pragma once

#include "Config.h"
#include "Missile.h"
#include "GameField.h"
#include <vector>
#include <typeinfo>

/**
* \brief Main class for enemy, containing all variables and some default methods.
*/
class Enemy
{
public:

	/**
	* \brief Enemy x coordinate 
	*/
	double x;


	/**
	* \brief Enemy y coordinate
	*/
	double y;


	/**
	* \brief Enemy horizontal speed vector
	*/
	double Vx;
	
	
	/**
	* \brief Enemy vertical speed vector
	*/
	double Vy;
	
	
	/**
	* Enemy is a ball, size defines the ball's radius.
	*
	* \brief Enemy size, in pixels.
	*/
	int size;
	
	
	/**
	* \brief y coordinate value at which enemies will bounce off.
	*/
	double bounceY;
	
	
	/**
	* \brief Enemy type flag.
	*/
	enum EnemyType { DIAGONAL, SHOOTINGDIAGONAL, GROUPPER, BLOCKER } enemyType;
	

	/**
	* Enemy colour, defined by struct in Config.h. Contains of red, green, blue and alpha values, ranging from 0-255.
	*
	* \brief Enemy colour.
	*/
	Colour colour;


	/**
	* \brief List of enemies.
	*/
	static std::vector<Enemy *> enemyList;


	
	template <class T>
	/**
	* Template function that is being called as: GetInst<EnemyType1>().
	*
	* \brief Function returning a vector of enemies of said type.
	*
	* \return vector<Enemy *> Vector of enemies of wanted types.
	*/
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
	/**
	* Template function that is being called as: GetInst<EnemyType1, EnemyType2,...>().
	*
	* \brief Function returning a vector of enemies of said type.
	*
	* \return vector<Enemy *> Vector of enemies of wanted types.
	*/
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
	

	/**
	* \brief Moves an enemy. Directly down for main class.
	*
	* \param float timeStep
	*/
	virtual void Move(float timeStep);


	/**
	* \brief Calls specific Move methods on all enemies on enemyList vector.
	*
	* \param float timeStep
	*/
	static void MoveAll(float timeStep);


	/**
	* \brief Performs an action enemy is supposed to do. Nothing for main class.
	*/
	virtual void Act() {}
	

	/**
	* \brief Virtual destructor for polimorphism
	*/
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


/**
* \brief Enemy that moves in diagonal instead of directly down.
*/
class EnemyDiagonal : public Enemy {
public:
	EnemyDiagonal(int x = 0, int dirX = 1) : Enemy(x, dirX) {
															enemyType = DIAGONAL;
															colour = { 255, 255, 0, 255 };
															}

	/**
	* \brief Moves enemy in diagonal, much faster in horizontal axis.
	*/
	void Move(float);


};


/**
* \brief EnemyDiagonal that fires missiles.
*/
class EnemyShooting : public EnemyDiagonal {
public:
	EnemyShooting(int x = 0, int dirX = 1) : EnemyDiagonal(x, dirX) { 
																	enemyType = SHOOTINGDIAGONAL; 
																	colour = { 255, 0, 0, 255 };
																	}
	EnemyShooting(Enemy&);

	/**
	* \brief Fires a Missile.
	*/
	void Act();

};


/**
* \brief Enemy that changes all regular enemies of type EnemyDiagonal into EnemyShooting (in its vincinity).
*/
class EnemyGroupper : public Enemy {
public:
	EnemyGroupper(int x = 0, int dirX = 1) : Enemy(x, dirX) {
															enemyType = GROUPPER;
															colour = { 0, 255, 125, 255 };
															}

	/**
	* \brief Looks for EnemyDiagonal nearby and converts them to EnemyShooting,
	*/
	void Act();

};


/**
* \brief Enemy placing blocks.
*/
class EnemyBlocker : public Enemy {
public:
	EnemyBlocker(int x = 0, int dirX = 1) : Enemy(x, dirX) {
															enemyType = BLOCKER;
															colour = { 255, 0, 255, 255 };
															}

	/**
	* \brief Places a regular block on its position, if no block exists.
	*/
	void Act();
};
