#include "Enemy.h"

std::vector<Enemy*> Enemy::enemyList;


Enemy::~Enemy()
{
	for (int i = 0; i < enemyList.size(); i++) {
		if (enemyList[i] == this) //then erase from vector
			enemyList.erase(enemyList.begin() + i);
	}
}

void Enemy::Move(float timeStep) {

	double ynew;
	ynew = this->y + (Vy*timeStep);


	//disappearing at the bottom
	if (!bounceY && ynew > SCREEN_HEIGHT) {
		delete this;
	}
	//or bouncing at y = bounceY
	else if (bounceY > 0 && ynew > bounceY) {
		Vy = -ENEMY_SPEED / 10;
	}
	//or bouncing from the top
	else if (ynew <= 0) {
		Vy = ENEMY_SPEED / 10;
	}

	this->y = ynew;

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

EnemyShooting::EnemyShooting(Enemy& obj) {

	EnemyShooting *aux = new EnemyShooting(obj.x, !signbit(obj.Vx));
	aux->x = obj.x;
	aux->y = obj.y;
	aux->Vx = obj.Vx;
	aux->Vy = obj.Vy;
	aux->size = obj.size;
	aux->bounceY = obj.bounceY;

	
	
}

void EnemyGroupper::Act() {

	//Get a list of enemies of a type
	std::vector<Enemy *> enList = Enemy::GetInst<EnemyDiagonal>();

	for (int i = 0; i < enList.size(); i++) {

		Enemy *auxe;

		auxe = enList[i];

		if (auxe->enemyType == DIAGONAL) {
			double distance;

			distance = (this->x - auxe->x)*(this->x - auxe->x) + (this->y - auxe->y)*(this->y - auxe->y);

			if (distance < 2000) {
				EnemyShooting auxx(*auxe);
				delete enList[i];
			}
		}
	}

}

void EnemyBlocker::Act() {

	//Check if field on matrix is occupied
	if (!GameField::getInstance().blockMatrix[int(this->x) / BLOCK_WIDTH][int(this->y) / BLOCK_HEIGHT]) {
		//if it's not
		//Add a block  to that place
		GameField::getInstance().AddBlock(int(this->x) / BLOCK_WIDTH, int(this->y) / BLOCK_HEIGHT, REGULAR);
	}

}