#include "Missile.h"



std::vector<Missile *> Missile::missileList;


Missile::Missile()
{
	this->x = 0;
	this->y = 0;
	this->Vy = MISSILE_SPEED;
	missileList.push_back(this);
}

Missile::Missile(double x, double y, int s) {
	this->x = x;
	this->y = y;
	this->Vy = s;
	missileList.push_back(this);
}

//Removes missile from the vector 
Missile::~Missile()
{
	for (int i = 0; i < missileList.size(); i++) {
		if (missileList[i] == this) {
			missileList.erase(missileList.begin() + i);
		}

	}
}


Block* Missile::CheckCollision() {
	Block *aux = 0;
	for (int i = 0; i < GameField::getInstance().blockList.size(); i++) {
		aux = GameField::getInstance().blockList[i];
		if (this->x >= aux->x && this->x < aux->x + BLOCK_WIDTH) {
			if (this->y > aux->y && this->y <= aux->y + BLOCK_HEIGHT) {
				return aux;
			}
		}
	}
	return 0;
}


char Missile::Move(float timeStep) {
	double ynew = this->y + (Vy*timeStep);
	Block *aux = CheckCollision();
	if (aux == 0) {
		this->y = ynew;
		if (this->y > SCREEN_HEIGHT || this->y < 0)
		{
			return -1;
		}
	}
	else {
		aux->Hit();
		return -1;
	}
	return 1;
}


void Missile::MoveAll(float timeStep) {
	for (int i = 0; i < missileList.size(); i++) {
		if (missileList[i]->Move(timeStep) == -1)
			delete missileList[i];
	}
}
