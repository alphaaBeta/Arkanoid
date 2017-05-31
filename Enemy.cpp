#include "Enemy.h"

std::vector<Enemy*> Enemy::enemyList;


Enemy::~Enemy()
{
	for (int i = 0; i < enemyList.size(); i++) {
		if (enemyList[i] == this) //then erase from vector
			enemyList.erase(enemyList.begin() + i);
	}
}

void Enemy::MoveAll(float timeStep) {
	for (int i = 0; i < Enemy::enemyList.size(); i++) {
		Enemy::enemyList[i]->Move(timeStep);
	}
}

void EnemyDiagonal::Move(float timeStep) {
	double xnew, ynew;
	xnew = this->x + (Vx * timeStep);
	ynew = this->y + (Vy * timeStep);


	//bouncing off the walls
	if (xnew + size > SCREEN_WIDTH || xnew - size < 0) {
		Vx = -Vx;
	}

	//disappearing at the bottom
	if (!bounceY && ynew > SCREEN_HEIGHT) {
		delete this;
	}
	//or bouncing at y = bounceY
	else if (bounceY > 0 && ynew > bounceY) {
		Vy = -ENEMY_SPEED/10;
	}
	//or bouncing from the top
	else if (ynew <= 0) {
		Vy = ENEMY_SPEED/10;
	}
	x = xnew;
	y = ynew;

	
}

void EnemyShooting::Act() {

	Missile *aux = new Missile(this->x, this->y+size, MISSILE_SPEED);


}

