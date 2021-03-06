#include "Block.h"



void Block::Hit(int a) {
	this->health-=a;
	if (health == 0 || (health == -1 && a == 2)) {

		//Random chance of dropping a powerup
		if (rand() % 100 < 10) {
			Powerup *aux;
			int a = rand() % 8;
			switch (a) {
			case 0:
				aux = new BigBallPWUP(double(this->x), double(this->y));
				break;
			case 1:
				aux = new TripleBallPWUP(double(this->x), double(this->y));
				break;
			case 2:
				aux = new ShootPWUP(double(this->x), double(this->y));
				break;
			case 3:
				aux = new ExtraLivePWUP(double(this->x), double(this->y));
				break;
			case 4:
				aux = new BigRacketPWUP(double(this->x), double(this->y));
				break;
			case 5:
				aux = new SmallRacketPWUP(double(this->x), double(this->y));
				break;
			case 6:
				aux = new FastBallPWUP(double(this->x), double(this->y));
				break;
			case 7:
				aux = new SlowBallPWUP(double(this->x), double(this->y));
				break;
			}


			GameField::getInstance().powerupList.push_back(aux);
		}

		delete this;
		Player::getInstance().score += 100;	//incrase player score
	}
	else if (health < 0) {	//indestructible blocks remain indestructible
		health = 0;
	}
}

Block::~Block() {
	
	

	//Removes the block from the block list-vector
	for (int i = 0; i < (GameField::getInstance()).blockList.size(); i++) {
		if ((GameField::getInstance()).blockList[i] == this) {
			//Wowie
			(GameField::getInstance()).blockList.erase\
				((GameField::getInstance()).blockList.begin() + i);
		}
	}

	//Sets the block pointer to 0 on array.
	GameField::getInstance().blockMatrix[this->x / BLOCK_WIDTH][this->y / BLOCK_HEIGHT] = 0;

}